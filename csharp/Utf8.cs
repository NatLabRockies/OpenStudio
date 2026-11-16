using System;
using System.Runtime.InteropServices;
using System.Text;

namespace OpenStudio
{
    internal static class Utf8
    {
        internal static byte[] ToNative(string text)
        {
            if (text == null) return null;
            byte[] bytes = new byte[checked(Encoding.UTF8.GetByteCount(text) + 1)];
            Encoding.UTF8.GetBytes(text, 0, text.Length, bytes, 0);
            return bytes;
        }

        internal static string FromNative(IntPtr pointer)
        {
            if (pointer == IntPtr.Zero) return null;
            int length = 0;
            while (Marshal.ReadByte(pointer, length) != 0) length = checked(length + 1);
            byte[] bytes = new byte[length];
            Marshal.Copy(pointer, bytes, 0, length);
            return Encoding.UTF8.GetString(bytes);
        }
    }
}
