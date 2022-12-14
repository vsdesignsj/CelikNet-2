/*  
	This file is part of CelikNET.

    CelikNET is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    CelikNET is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License along with CelikNET.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"

#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

namespace CelikNET {

	public ref class CelikException sealed: Exception 
	{
	public: 
		CelikException(String^ message, int ErrorCode): Exception(message), _EIDErrorCode(ErrorCode) {}
		property int EIDErrorCode { int get() { return _EIDErrorCode; }; }
		property String^ EIDErrorDescriptionEn { 
			String^ get() 
			{
				switch(EIDErrorCode) 
				{
					case EID_OK: return "Operation completed succesfully"; 
					case EID_E_GENERAL_ERROR: return "General error";
					case EID_E_INVALID_PARAMETER: return "Invalid parameter";
					case EID_E_VERSION_NOT_SUPPORTED: return "Version not supported";
					case EID_E_NOT_INITIALIZED: return "Not initialized";
					case EID_E_UNABLE_TO_EXECUTE: return "Unable to execute";
					case EID_E_READER_ERROR: return "Reader error";
					case EID_E_CARD_MISSING: return "Card missing";
					case EID_E_CARD_UNKNOWN: return "Card unknown";
					case EID_E_CARD_MISMATCH: return "Card mismatch";
					case EID_E_UNABLE_TO_OPEN_SESSION: return "Unable to open session";
					case EID_E_DATA_MISSING: return "Data missing";
					case EID_E_CARD_SECFORMAT_CHECK_ERROR: return "Card security format check error";
					case EID_E_SECFORMAT_CHECK_CERT_ERROR: return "Security format check certificate error";
					default: return "Unknown error, consult documentation";
				}
			}; 
		}
		property String^ EIDErrorDescriptionSr { 
			String^ get() 
			{
				switch(EIDErrorCode) 
				{
					case EID_OK: return L"Операција успешно завршена"; 
					case EID_E_GENERAL_ERROR: return L"Општа грешка";
					case EID_E_INVALID_PARAMETER: return L"Неисправан параметар";
					case EID_E_VERSION_NOT_SUPPORTED: return L"Ова верзија API-a није подржана";
					case EID_E_NOT_INITIALIZED: return L"Библиотека није иницијализована";
					case EID_E_UNABLE_TO_EXECUTE: return L"Библиотека не може извршити операцију";
					case EID_E_READER_ERROR: return L"Грешка у читачу картица";
					case EID_E_CARD_MISSING: return L"Картица није присутна у читачу";
					case EID_E_CARD_UNKNOWN: return L"Непозната картица у читачу";
					case EID_E_CARD_MISMATCH: return L"Погрешна картица у читачу";
					case EID_E_UNABLE_TO_OPEN_SESSION: return L"Библиотека не може да отвори сесију";
					case EID_E_DATA_MISSING: return L"Подаци нису присутни на картици";
					case EID_E_CARD_SECFORMAT_CHECK_ERROR: return L"Сигурносна грешка у формату картице";
					case EID_E_SECFORMAT_CHECK_CERT_ERROR: return L"Грешка при провери сертификата на картици";
					default: return L"Непозната грешка, консултујте документацију";
				}
			}; 
		}

	private:
		int _EIDErrorCode;
	};


	// data strukture
	// --------------------------------------------------------------------------------------------------

	/// <summary>
	/// Sadrzi osnovne informacije o licnoj karti
	/// </summary>
	public ref struct DocumentData
	{
	public:
		String^ docRegNo;
		String^ issuingDate;
		String^ expiryDate;
		String^ issuingAuthority;
	};
	/// <summary>
	/// Sadrzi osnovne informacije o nosiocu licne karte
	/// </summary>
	public ref struct FixedPersonalData
	{
	public:
		String^ personalNumber;
		String^ surname;
		String^ givenName;
		String^ parentGivenName;
		String^ sex;
		String^ placeOfBirth;
		String^ stateOfBirth;
		String^ dateOfBirth;
		String^ communityOfBirth;
	};

	/// <summary>
	/// Sadrzi dodatne informacije o nosiocu licne karte
	/// </summary>
	public ref struct VariablePersonalData
	{
	public:
		String^ state;
		String^ community;
		String^ place;
		String^ street;
		String^ houseNumber;
		String^ houseLetter;
		String^ entrance;
		String^ floor;
		String^ apartmentNumber;
	};

	// interop klasa
	// --------------------------------------------------------------------------------------------------

	public ref class CelikInterop sealed
	{
	private:
		/// <summary>
		/// nested klasa koja sluzi kao global destructor/finalizer
		/// </summary>
		ref class CelikInteropCleaner sealed
		{
		internal:
			static CelikInteropCleaner^ _instance = gcnew CelikInteropCleaner();
			static property CelikInteropCleaner^ singleton { CelikInteropCleaner^ get() { return _instance; } }
		private:
			CelikInteropCleaner() {}
			~CelikInteropCleaner() { this->!CelikInteropCleaner(); }
			!CelikInteropCleaner() 
			{
				// ovaj exception ako bude bice na kraju same aplikacije, ostavljen je zbog debug sesija
				int err;
				if ((err = EidCleanup()) != EID_OK) throw gcnew CelikException("Cleanup nije izvrsen", err);
			} 
		};

		static CelikInteropCleaner^  _cleaner;
		/// <summary>
		/// Globalni konstruktor za Celik Interop wrapper. Inicijalizuje Celik API, poziva se "skriveno" samo jednom
		/// </summary>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko Celik Startup nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		static CelikInterop() 
		{
			int err;
			if ((err = EidStartup(3)) != EID_OK) throw gcnew CelikException("Startup nije izvrsen", err);
			// startup je ok, kreiraj cleaner "singleton" ciji teardown ce ugasiti celik za slucaj da korisnik zaboravi
			_cleaner = CelikInteropCleaner::singleton;
		}

		// static dummy
		static int _dummy = 123;

	public:
		/// <summary>
		/// Globalni cleanup za Celik Interop wrapper. Ovo je poslednji CelikNET poziv u aplikaciji, posle njega vise nece raditi instanciranje i pozivanje CelikNET objekata/metoda. Alternativno mozete pustiti aplikaciju da se sama ocisti
		/// </summary>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko Celik Cleanup nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		static void Cleanup() 
		{
			//manuelni tear down celika, ako je cleaner inicijalizovan ovo ce deterministicki pozvadi dispose patern i uraditi zatvaranje 
			delete _cleaner;
		}

		/// <summary>
		/// Konstruktor za Celik Interop wrapper. Inicijalizuje Read operaciju kroz EidBeginRead i omogucava poziv blok komandi
		/// </summary>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko BeginRead nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		CelikInterop(LPCSTR szReader)
		{
			// pipni staticko polje da bi naterao kompajler da pozove sttaicki konstruktor prvi put
			// http://connect.microsoft.com/VisualStudio/feedback/details/611716/c-cli-class-static-constructor-not-called-in-release-build
			int dummy = CelikInterop::_dummy;
			// init read
			int err;
			if ((err = EidBeginRead(szReader)) != EID_OK) throw gcnew CelikException("BeginRead nije izvrsen", err);
		}

		~CelikInterop() 
		{
			// dispose pattern, pozovi finalizer
			this->!CelikInterop();
		}


		/// <summary>
		/// Ucitava osnovne podatke sa licne karte
		/// </summary>
		/// <returns>Instanca <see cref="CelikNET::FixedPersonalData">CelikNET::FixedPersonalData</see> klase u kojoj su podaci</returns>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko ReadFixedPersonalData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		FixedPersonalData^ ReadFixedPersonalData() 
		{
			msclr::lock l(CelikInteropCleaner::singleton); // thread global sync
			int err;
			PEID_FIXED_PERSONAL_DATA p = new EID_FIXED_PERSONAL_DATA;
			if ((err = EidReadFixedPersonalData(p)) != EID_OK) throw gcnew CelikException("ReadFixedPersonalData nije izvrsen", err);
			FixedPersonalData^ fpd = gcnew FixedPersonalData;
			fpd->personalNumber = decodeUTF8Buffer(p->personalNumber, p->personalNumberSize);
			fpd->surname = decodeUTF8Buffer(p->surname, p->surnameSize);
			fpd->givenName = decodeUTF8Buffer(p->givenName, p->givenNameSize);
			fpd->parentGivenName = decodeUTF8Buffer(p->parentGivenName, p->parentGivenNameSize);
			fpd->sex = decodeUTF8Buffer(p->sex, p->sexSize);
			fpd->placeOfBirth = decodeUTF8Buffer(p->placeOfBirth, p->placeOfBirthSize);
			fpd->stateOfBirth = decodeUTF8Buffer(p->stateOfBirth, p->stateOfBirthSize);
			fpd->dateOfBirth = decodeUTF8Buffer(p->dateOfBirth, p->dateOfBirthSize);
			fpd->communityOfBirth = decodeUTF8Buffer(p->communityOfBirth, p->communityOfBirthSize);
			return fpd;
		}


		/// <summary>
		/// Ucitava dodatne podatke sa licne karte
		/// </summary>
		/// <returns>Instanca <see cref="CelikNET::VariablePersonalData">CelikNET::VariablePersonalData</see> klase u kojoj su podaci</returns>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko ReadVariabelPersonalData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		VariablePersonalData^ ReadVariablePersonalData() 
		{
			msclr::lock l(CelikInteropCleaner::singleton); // thread global sync
			int err;
			PEID_VARIABLE_PERSONAL_DATA p = new EID_VARIABLE_PERSONAL_DATA;
			if ((err = EidReadVariablePersonalData(p)) != EID_OK) throw gcnew CelikException("ReadVariablePersonalData nije izvrsen", err);
			VariablePersonalData^ vpd = gcnew VariablePersonalData;
			vpd->state = decodeUTF8Buffer(p->state, p->stateSize);
			vpd->community = decodeUTF8Buffer(p->community, p->communitySize);
			vpd->place = decodeUTF8Buffer(p->place, p->placeSize);
			vpd->street = decodeUTF8Buffer(p->street, p->streetSize);
			vpd->houseNumber = decodeUTF8Buffer(p->houseNumber, p->houseNumberSize);
			vpd->houseLetter = decodeUTF8Buffer(p->houseLetter, p->houseLetterSize);
			vpd->entrance = decodeUTF8Buffer(p->entrance, p->entranceSize);
			vpd->floor = decodeUTF8Buffer(p->floor, p->floorSize);
			vpd->apartmentNumber = decodeUTF8Buffer(p->apartmentNumber, p->apartmentNumberSize);
			return vpd;
		}

		/// <summary>
		/// Ucitava osnovne podatke sa licne karte
		/// </summary>
		/// <returns>Instanca <see cref="CelikNET::DocumentData">CelikNET::DocumentData</see> klase u kojoj su podaci</returns>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko ReadDocumentData nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		DocumentData^ ReadDocumentData() 
		{
			msclr::lock l(CelikInteropCleaner::singleton); // thread global sync
			int err;
			PEID_DOCUMENT_DATA p = new EID_DOCUMENT_DATA;
			if ((err = EidReadDocumentData(p)) != EID_OK) throw gcnew CelikException("ReadDocumentData nije izvrsen", err);
			DocumentData^ dd = gcnew DocumentData;
			dd->docRegNo = decodeUTF8Buffer(p->docRegNo, p->docRegNoSize);
			dd->issuingDate = decodeUTF8Buffer(p->issuingDate, p->issuingDateSize);
			dd->expiryDate = decodeUTF8Buffer(p->expiryDate, p->expiryDateSize);
			dd->issuingAuthority = decodeUTF8Buffer(p->issuingAuthority, p->issuingAuthoritySize);
			return dd;
		}


		/// <summary>
		/// Ucitava sliku sa licne karte
		/// </summary>
		/// <returns>Instanca <see cref="System::Drawing::Bitmap">System.Drawing.Bitmap</see> klase u kojoj je slika licne karte</returns>
		/// <exception cref="CelikNET::CelikException">Bacen ukoliko ReadPortrait nije prosao kako treba, kod greske je ukljucen u tekst exceptiona</exception>
		Bitmap^ ReadProfileImage() 
		{
			msclr::lock l(CelikInteropCleaner::singleton); // thread global sync
			// izvuci bajtove portreta
			int err;
			PEID_PORTRAIT p = new EID_PORTRAIT;
			if ((err = EidReadPortrait(p)) != EID_OK) throw gcnew CelikException("ReadPortrait nije izvrsen", err);
			// iskopiraj sliku u managed space
			array<byte>^ managedArray = gcnew array<byte>(p->portraitSize);
			Marshal::Copy((IntPtr)p->portrait, managedArray, 0, p->portraitSize);
			// instanciraj bitmap sa jpeg nizom
			MemoryStream^ ms = gcnew MemoryStream(managedArray);
			return gcnew Bitmap(ms);
		}

	private:
		String^ decodeUTF8Buffer(char* buffer, int length) 
		{
			array<byte>^ managedArray = gcnew array<byte>(length);
			Marshal::Copy((IntPtr)buffer, managedArray, 0, length);
			return Encoding::UTF8->GetString(managedArray, 0, length);
		}

	protected:
		!CelikInterop() 
		{
			int err;
			if ((err = EidEndRead()) != EID_OK) throw gcnew CelikException("EndRead nije izvrsen", err);
		} 
	};
}



