/*  
	This file is part of CelikNET.

    CelikNET is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    CelikNET is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with CelikNET.  If not, see <http://www.gnu.org/licenses/>.
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace ConsoleTester
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.GetEncoding(1251);
            try
            {
                string str = "OMNIKEY AG Smart Card Reader USB 0\0";
                byte[] bytes = Encoding.ASCII.GetBytes(str);


                unsafe
                {
                    sbyte* sp;

                    fixed (byte* p = bytes)
                    {
                        sp = (sbyte*)p;
                        //SP is now what you want
                    }

                    using (CelikNET.CelikInterop x = new CelikNET.CelikInterop(sp))
                    {
                        Console.WriteLine("Podaci o licnoj karti ------------------------------------------");
                        CelikNET.DocumentData d3 = x.ReadDocumentData();
                        Console.WriteLine("docRegNo: {0}", d3.docRegNo);
                        Console.WriteLine("issuingDate: {0}", d3.issuingDate);
                        Console.WriteLine("expiryDate: {0}", d3.expiryDate);
                        Console.WriteLine("issuingAuthority: {0}", d3.issuingAuthority);

                        Console.WriteLine("Fiksni podaci ------------------------------------------");
                        CelikNET.FixedPersonalData d1 = x.ReadFixedPersonalData();
                        Console.WriteLine("personalNumber: {0}", d1.personalNumber);
                        Console.WriteLine("surname: {0}", d1.surname);
                        Console.WriteLine("givenName: {0}", d1.givenName);
                        Console.WriteLine("sex: {0}", d1.sex);
                        Console.WriteLine("placeOfBirth: {0}", d1.placeOfBirth);
                        Console.WriteLine("stateOfBirth: {0}", d1.stateOfBirth);
                        Console.WriteLine("dateOfBirth: {0}", d1.dateOfBirth);
                        Console.WriteLine("communityOfBirth: {0}", d1.communityOfBirth);

                        Console.WriteLine("Variablini podaci ------------------------------------------");
                        CelikNET.VariablePersonalData d2 = x.ReadVariablePersonalData();
                        Console.WriteLine("state: {0}", d2.state);
                        Console.WriteLine("community: {0}", d2.community);
                        Console.WriteLine("place: {0}", d2.place);
                        Console.WriteLine("street: {0}", d2.street);
                        Console.WriteLine("houseNumber: {0}", d2.houseNumber);
                        Console.WriteLine("houseLetter: {0}", d2.houseLetter);
                        Console.WriteLine("entrance: {0}", d2.entrance);
                        Console.WriteLine("floor: {0}", d2.floor);
                        Console.WriteLine("apartmentNumber: {0}", d2.apartmentNumber);

                        Console.WriteLine("Slika ------------------------------------------");
                        Bitmap c = x.ReadProfileImage();
                        Console.WriteLine("Ucitana slika {0}x{1}", c.Width, c.Height);
                    }
                    Console.ReadLine();
                }
            }
            catch (CelikNET.CelikException ex)
            {
                Console.WriteLine("EXCEPTION: {0} {1}", ex.EIDErrorCode, ex.EIDErrorDescriptionEn);
                Console.ReadLine();
                throw ex;
            }

        }
        public static byte[] GetBytesFromStringWithZero(Encoding encoding, string str)
        {
            int len = encoding.GetByteCount(str);

            // Here we leave a "space" for the ending \0
            // Note the trick to discover the length of the \0 in the encoding:
            // It could be 1 (for Ansi, Utf8, ...), 2 (for Unicode, UnicodeBE), 4 (for UTF32)
            // We simply ask the encoder how long it would be to encode it :-)
            byte[] bytes = new byte[len + encoding.GetByteCount("\0")];
            encoding.GetBytes(str, 0, str.Length, bytes, 0);
            return bytes;
        }
    }
}
