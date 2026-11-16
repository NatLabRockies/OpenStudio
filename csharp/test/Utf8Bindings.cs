using System;
using System.IO;
using System.Reflection;
using System.Text;
using OpenStudio;

// Standalone regression executable; compile against OpenStudio.dll and .NET 4.5.
internal static class Utf8Bindings
{
    private static int assertions;

    private static void Check(bool condition, string message)
    {
        if (!condition) throw new Exception(message);
        ++assertions;
    }

    private sealed class UnicodeMeasure : EnergyPlusMeasure
    {
        internal string Text;
        internal int NameCalls;

        public override string name()
        {
            ++NameCalls;
            return Text;
        }
    }

    private sealed class UnicodeRunner : OSRunner
    {
        internal string LastError;
        internal int ErrorCalls;

        internal UnicodeRunner(WorkflowJSON workflow) : base(workflow) { }

        public override void registerError(string message)
        {
            LastError = message;
            ++ErrorCalls;
        }
    }

    private static void CheckDirectors(string[] samples)
    {
        // Direct C# calls stay in the override; base.name() bypasses native
        // virtual dispatch. Invoke the existing native entry point instead.
        Type pinvoke = typeof(OSMeasure).Assembly.GetType("OpenStudio.OpenStudioMeasurePINVOKE", true);
        MethodInfo nativeName = pinvoke.GetMethod("OSMeasure_name", BindingFlags.Public | BindingFlags.Static);
        MethodInfo getPointer = typeof(OSMeasure).GetMethod("getCPtr", BindingFlags.NonPublic | BindingFlags.Static);
        Check(nativeName != null && getPointer != null, "Cannot find the native measure name entry point.");

        using (var measure = new UnicodeMeasure())
        using (var workflow = new WorkflowJSON())
        using (var runner = new UnicodeRunner(workflow))
        using (var userArguments = new OSArgumentMap())
        {
            object pointer = getPointer.Invoke(null, new object[] { measure });
            for (int i = 0; i < 1000; ++i)
            {
                // Verify wrapper fields keep callback delegates alive across
                // collections before native calls use them.
                if (i % 100 == 0) { GC.Collect(); GC.WaitForPendingFinalizers(); GC.Collect(); }
                measure.Text = i % 10 == 0 ? "" : samples[i % samples.Length];
                string actual = (string)nativeName.Invoke(null, new object[] { pointer });
                Check(actual == measure.Text, "Director return text was corrupted.");
                Check(measure.NameCalls == i + 1, "Native measure virtual dispatch did not reach the override.");

                string argumentName = "required-" + samples[i % samples.Length];
                using (var arguments = new OSArgumentVector())
                using (var argument = OSArgument.makeStringArgument(argumentName, true))
                {
                    arguments.Add(argument);
                    Check(!runner.validateUserArguments(arguments, userArguments), "Missing required argument was accepted.");
                }
                Check(runner.ErrorCalls == i + 1, "Native runner virtual dispatch did not reach the override.");
                Check(runner.LastError.Contains(argumentName), "Director argument text was corrupted.");
            }
        }
    }

    private static int Main(string[] args)
    {
        string root = args.Length == 0 ? System.IO.Path.Combine(System.IO.Path.GetTempPath(), "OpenStudioUtf8-" + Guid.NewGuid().ToString("N")) : args[0];
        Directory.CreateDirectory(root);
        Console.WriteLine("Assembly: " + typeof(OpenStudioUtilitiesCore).Assembly.FullName);
        Console.WriteLine("CLR version: " + Environment.Version);
        Console.WriteLine("Process bits: " + IntPtr.Size * 8);
        Console.WriteLine("Output: " + root);

        string[] samples = { "ASCII", "dash-\u2013", "euro-\u20ac", "accent-\u00e9", "polish-\u0142", "chinese-\u4e2d", "emoji-\U0001f600", "combining-e\u0301", "literal-\u00c3\u00a9" };
        try
        {
            using (var idf = new IdfFile(new IddFileType("EnergyPlus")))
            using (var values = new StringVector())
            {
                foreach (string sample in samples)
                {
                    string file = System.IO.Path.Combine(root, sample, sample + ".idf");
                    Directory.CreateDirectory(System.IO.Path.GetDirectoryName(file));
                    idf.setHeader(sample);
                    Check(idf.header().Contains(sample), "Header round trip failed: " + sample);
                    using (var path = OpenStudioUtilitiesCore.toPath(file))
                    {
                        Check(OpenStudioUtilitiesCore.toString(path) == file.Replace('\\', '/'), "Path round trip failed: " + sample);
                        Check(idf.save(path, true), "Save failed: " + sample);
                        Check(File.Exists(file), "Saved to a different path: " + sample);
                        Check(OpenStudioUtilitiesCore.exists(path), "Native exists failed: " + sample);
                        using (var loaded = IdfFile.load(path)) Check(loaded.is_initialized(), "Load failed: " + sample);
                    }
                    Check(File.ReadAllText(file, new UTF8Encoding(false, true)).Contains(sample), "File text was corrupted: " + sample);
                    values.Add(sample);
                    Check(values[values.Count - 1] == sample, "StringVector round trip failed: " + sample);
                }

                // EnumBase uppercases the rejected name before formatting its error.
                string invalid = "INVALID-\u2013-\u4e2d-\U0001f600";
                bool caught = false;
                try { using (var type = new IddFileType(invalid)) { } }
                catch (Exception exception)
                {
                    caught = true;
                    Check(exception.Message.Contains(invalid), "Exception message was corrupted: " + exception.Message);
                }
                Check(caught, "Expected an exception for an invalid enum name.");

                caught = false;
                try { using (var path = OpenStudioUtilitiesCore.toPath(null)) { } }
                catch (ArgumentNullException) { caught = true; }
                Check(caught, "Null string handling changed.");
                using (var empty = OpenStudioUtilitiesCore.toPath("")) Check(OpenStudioUtilitiesCore.toString(empty) == "", "Empty path handling changed.");

                // Exercise ordinary string-result callbacks across managed collections.
                for (int i = 0; i < 100000; ++i)
                {
                    Check(values[i % samples.Length] == samples[i % samples.Length], "Repeated callback failed.");
                    if (i % 10000 == 0) { GC.Collect(); GC.WaitForPendingFinalizers(); }
                }
            }

            CheckDirectors(samples);

            using (var model = new Model())
            using (var space = new Space(model))
            using (var zone = new ThermalZone(model))
            using (var translator = new EnergyPlusForwardTranslator())
            {
                string name = "space-\u2013-\u00e9-\u4e2d-\U0001f600";
                space.setName(name);
                zone.setName(name + "-zone");
                space.setThermalZone(zone);
                Check(space.nameString() == name, "Model module string round trip failed.");
                using (var workspace = translator.translateModel(model))
                using (var idf = workspace.toIdfFile())
                using (var path = OpenStudioUtilitiesCore.toPath(System.IO.Path.Combine(root, "translated-\u2013.idf")))
                    Check(idf.save(path, true), "Translator module save failed.");
                Check(File.Exists(System.IO.Path.Combine(root, "translated-\u2013.idf")), "Translator output path was corrupted.");
                Check(File.ReadAllText(System.IO.Path.Combine(root, "translated-\u2013.idf"), new UTF8Encoding(false, true)).Contains(name + "-zone"), "Translator output text was corrupted.");
            }

            Console.WriteLine("PASS: " + assertions + " assertions, " + samples.Length + " character cases.");
            return 0;
        }
        catch (Exception exception)
        {
            Console.Error.WriteLine(exception);
            return 1;
        }
    }
}
