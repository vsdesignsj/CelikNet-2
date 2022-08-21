<?xml version="1.0"?><doc>
<members>
<member name="T:CelikNET.DocumentData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="85">
<summary>
Sadrzi osnovne informacije o licnoj karti
</summary>
</member>
<member name="T:CelikNET.FixedPersonalData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="96">
<summary>
Sadrzi osnovne informacije o nosiocu licne karte
</summary>
</member>
<member name="T:CelikNET.VariablePersonalData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="113">
<summary>
Sadrzi dodatne informacije o nosiocu licne karte
</summary>
</member>
<member name="T:CelikNET.CelikInterop.CelikInteropCleaner" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="136">
<summary>
nested klasa koja sluzi kao global destructor/finalizer
</summary>
</member>
<member name="M:CelikNET.CelikInterop.#cctor" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="156">
<summary>
Globalni konstruktor za Celik Interop wrapper. Inicijalizuje Celik API, poziva se "skriveno" samo jednom
</summary>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko Celik Startup nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.Cleanup" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="172">
<summary>
Globalni cleanup za Celik Interop wrapper. Ovo je poslednji CelikNET poziv u aplikaciji, posle njega vise nece raditi instanciranje i pozivanje CelikNET objekata/metoda. Alternativno mozete pustiti aplikaciju da se sama ocisti
</summary>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko Celik Cleanup nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.#ctor(System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte!System.Runtime.CompilerServices.IsConst*)" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="182">
<summary>
Konstruktor za Celik Interop wrapper. Inicijalizuje Read operaciju kroz EidBeginRead i omogucava poziv blok komandi
</summary>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko BeginRead nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.ReadFixedPersonalData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="203">
<summary>
Ucitava osnovne podatke sa licne karte
</summary>
<returns>Instanca <see cref="T:CelikNET.FixedPersonalData">CelikNET::FixedPersonalData</see> klase u kojoj su podaci</returns>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko ReadFixedPersonalData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.ReadVariablePersonalData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="228">
<summary>
Ucitava dodatne podatke sa licne karte
</summary>
<returns>Instanca <see cref="T:CelikNET.VariablePersonalData">CelikNET::VariablePersonalData</see> klase u kojoj su podaci</returns>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko ReadVariabelPersonalData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.ReadDocumentData" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="252">
<summary>
Ucitava osnovne podatke sa licne karte
</summary>
<returns>Instanca <see cref="T:CelikNET.DocumentData">CelikNET::DocumentData</see> klase u kojoj su podaci</returns>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko ReadDocumentData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
<member name="M:CelikNET.CelikInterop.ReadProfileImage" decl="false" source="C:\Users\Cyber\Downloads\CelikNET-Source2\CelikNET\CelikNET.cpp" line="272">
<summary>
Ucitava sliku sa licne karte
</summary>
<returns>Instanca <see cref="T:System.Drawing.Bitmap">System.Drawing.Bitmap</see> klase u kojoj je slika licne karte</returns>
<exception cref="T:CelikNET.CelikException">Bacen ukoliko ReadPortrait nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
</member>
</members>
</doc>