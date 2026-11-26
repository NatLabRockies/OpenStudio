/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Energy Innovation, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#include <algorithm>
#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <stdio.h>
#include <assert.h>
#include <zlib.h>

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

struct EmbeddedFile
{
  std::string infile;
  std::string outfile;
  std::string filenum;
  std::string embeddedname;
};

static int embedFile(const EmbeddedFile& file) {
  const auto* infile = file.infile.c_str();
  const auto* outfile = file.outfile.c_str();
  const auto* filenum = file.filenum.c_str();
  const auto* embeddedname = file.embeddedname.c_str();

  std::error_code ec;
  std::filesystem::create_directories(std::filesystem::path(file.outfile).parent_path(), ec);

  z_stream strm;
  unsigned char in[CHUNK];
  unsigned char out[CHUNK];

  /* allocate deflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  int ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
  if (ret != Z_OK) return 1;

  FILE* source = fopen(infile, "rb");
  if (source == NULL) {
    std::cerr << "Could not open '" << infile << "' for reading" << std::endl;
    return EXIT_FAILURE;
  }

  std::fstream outstream(outfile, std::fstream::out | std::fstream::trunc);

  if (outstream.is_open()) {
    outstream << "static const uint8_t embedded_file_" << filenum << "[] = {";
    int flush = 0;
    // This is the compressed length in chars;
    unsigned length = 0;
    do {
      strm.avail_in = fread(in, 1, CHUNK, source);
      if (ferror(source)) {
        (void)deflateEnd(&strm);
        return EXIT_FAILURE;
      }
      flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
      strm.next_in = in;

      /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
      do {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = deflate(&strm, flush);   /* no bad return value */
        assert(ret != Z_STREAM_ERROR); /* state not clobbered */
        unsigned have = CHUNK - strm.avail_out;

        for (unsigned i = 0; i != have; ++i) {
          if (length != 0) {
            outstream << ",";
          }
          outstream << "0x" << std::hex << static_cast<int>(out[i]);
          ++length;
        }
      } while (strm.avail_out == 0);
      assert(strm.avail_in == 0); /* all input will be used */

      /* done when last data in file processed */
    } while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END); /* stream will be complete */

    /* clean up and return */
    (void)deflateEnd(&strm);

    outstream << "};";

    outstream << "\n";
    outstream << "static const char *embedded_file_name_" << filenum << " = \"" << embeddedname << "\";";
    outstream << "\n";
    outstream << "static const size_t embedded_file_len_" << filenum << " = " << std::dec << length << ";";
    outstream << std::endl;

    outstream.close();
    fclose(source);
  } else {
    std::cout << "Could not open '" << outfile << "' for writing" << std::endl;
    return EXIT_FAILURE;
  }

  return 0;
}

// Usage: CreateEmbeddedSource <list_file>
// Each line of the list file is: <infile>\t<outfile>\t<filenum>\t<embeddedname>
// All files are processed in one go (on all cores), rather than one process per file
int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <list_file>" << std::endl;
    return EXIT_FAILURE;
  }

  std::ifstream list(argv[1]);
  if (!list.is_open()) {
    std::cerr << "Could not open '" << argv[1] << "' for reading" << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<EmbeddedFile> files;
  std::string line;
  while (std::getline(list, line)) {
    if (line.empty()) {
      continue;
    }
    EmbeddedFile file;
    size_t start = 0;
    for (auto* field : {&file.infile, &file.outfile, &file.filenum}) {
      const size_t tab = line.find('\t', start);
      if (tab == std::string::npos) {
        std::cerr << "Malformed line in '" << argv[1] << "': " << line << std::endl;
        return EXIT_FAILURE;
      }
      *field = line.substr(start, tab - start);
      start = tab + 1;
    }
    file.embeddedname = line.substr(start);
    files.push_back(std::move(file));
  }

  std::atomic<size_t> next{0};
  std::atomic<bool> failed{false};
  const unsigned nThreads = std::max(1U, std::thread::hardware_concurrency());
  std::vector<std::thread> threads;
  for (unsigned t = 0; t < nThreads; ++t) {
    threads.emplace_back([&]() {
      for (size_t i = next++; i < files.size(); i = next++) {
        if (embedFile(files[i]) != 0) {
          failed = true;
        }
      }
    });
  }
  for (auto& thread : threads) {
    thread.join();
  }

  return failed ? EXIT_FAILURE : 0;
}
