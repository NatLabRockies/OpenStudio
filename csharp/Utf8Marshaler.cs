using System;
using System.Runtime.InteropServices;
using System.Text;

namespace OpenStudio
{
    // Keep UTF-8 interop available on .NET Framework 4.5. Native string results
    // are allocated by the SWIG callback and freed by the outer P/Invoke call.
    internal sealed class Utf8Marshaler : ICustomMarshaler
    {
        private static readonly Utf8Marshaler Owned = new Utf8Marshaler(false);
        private static readonly Utf8Marshaler Borrowed = new Utf8Marshaler(true);
        private readonly bool borrowed;

        private Utf8Marshaler(bool borrowed)
        {
            this.borrowed = borrowed;
        }

        public static ICustomMarshaler GetInstance(string cookie)
        {
            return cookie == "borrowed" ? Borrowed : Owned;
        }

        public IntPtr MarshalManagedToNative(object value)
        {
            if (value == null) return IntPtr.Zero;
            var text = value as string;
            if (text == null) throw new MarshalDirectiveException("Expected a string.");

            byte[] bytes = Encoding.UTF8.GetBytes(text);
            IntPtr pointer = Marshal.AllocCoTaskMem(checked(bytes.Length + 1));
            Marshal.Copy(bytes, 0, pointer, bytes.Length);
            Marshal.WriteByte(pointer, bytes.Length, 0);
            return pointer;
        }

        public object MarshalNativeToManaged(IntPtr pointer)
        {
            if (pointer == IntPtr.Zero) return null;
            int length = 0;
            while (Marshal.ReadByte(pointer, length) != 0) length = checked(length + 1);
            byte[] bytes = new byte[length];
            Marshal.Copy(pointer, bytes, 0, length);
            return Encoding.UTF8.GetString(bytes);
        }

        public void CleanUpNativeData(IntPtr pointer)
        {
            // Callback arguments point into native strings and must not be freed.
            if (!borrowed) Marshal.FreeCoTaskMem(pointer);
        }

        public void CleanUpManagedData(object value) { }
        public int GetNativeDataSize() { return -1; }
    }
}
