using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;

namespace myfirst
{
    class Program
    {
        public static string HashFunction(byte[] mixedKey)
        {
            var byts = new byte[4];

            byts[0] = (byte) (mixedKey[0] ^ mixedKey[3] ^ mixedKey[5]);
            byts[1] = (byte) (mixedKey[0] | mixedKey[2] | mixedKey[4]);
            byts[2] = (byte) (mixedKey[1] ^ mixedKey[3] ^ mixedKey[5]);
            byts[3] = (byte) (mixedKey[1] & mixedKey[2] & mixedKey[4]);

            return Convert.ToBase64String(byts);
        }

        public static byte[] GetBytes(string str)
        {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

        public static string GenerateRandomSalt(RNGCryptoServiceProvider rng, int size)
        {
            var bytes = new byte[size];
            rng.GetBytes(bytes);
            return Convert.ToBase64String(bytes);
        }

        static void Main(string[] args)
        {
            var rng = new RNGCryptoServiceProvider();
            var salt = GenerateRandomSalt(rng, 6);
            var x = GetBytes(salt);
            Console.WriteLine("{0} {1}", salt, HashFunction(x));
        }
    }
}
