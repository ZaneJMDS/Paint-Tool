#include "FileInterface.h"

FileInterface::FileInterface()
{
}

FileInterface::~FileInterface()
{
}

// Load file from user's file explorer
void FileInterface::LoadFile(sf::RenderTexture* _texture)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileOpenDialog* pFileOpen;

		// Create the OFD
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog,
			reinterpret_cast<void**>(&pFileOpen));

		// L chooses the file type
		LPCWSTR szJPG = L"Jpeg";
		LPCWSTR szBMP = L"Bitmap";
		LPCWSTR szAll = L"ALL";

		COMDLG_FILTERSPEC rgSpec[] =
		{
			{szJPG, L"*.jpg;*.jpeg"},
			{szBMP, L"*.bmp"},
			{szAll, L"*.*"}
		};

		pFileOpen->SetFileTypes(3, rgSpec);

		if (SUCCEEDED(hr))
		{
			// Show the dialogue box
			hr = pFileOpen->Show(NULL);

			if (SUCCEEDED(hr))
			{
				// Get the name of the file
				IShellItem* pItem;
				hr = pFileOpen->GetResult(&pItem);

				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					if (SUCCEEDED(hr))
					{
						sf::Texture newTex(pszFilePath);
						sf::Sprite newSprite(newTex);

						_texture->draw(newSprite);
						_texture->display();

						MessageBoxW(NULL, L"Image loaded successfully", L"Success", MB_OK);
						CoTaskMemFree(pszFilePath);


					}
					// Water bucket RELEASE!!!
					pItem->Release();
				}
			}

			pFileOpen->Release();
		}
		CoUninitialize();
	}
}

// Code from Zac
// Save file to users file explorer
void FileInterface::SaveFile(sf::RenderTexture* _texture)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr))
	{
		IFileSaveDialog* pFileSave;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
			IID_IFileSaveDialog, reinterpret_cast<void**>(&pFileSave));

		if (SUCCEEDED(hr))
		{
			// Show the Save dialog box.
			hr = pFileSave->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem* pItem;
				hr = pFileSave->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						if (_texture->getTexture().copyToImage().saveToFile(pszFilePath))
						{
							MessageBoxW(NULL, pszFilePath, L"Saved to: ", MB_OK);
							CoTaskMemFree(pszFilePath);
						}
					}
					pItem->Release();
				}
			}
			pFileSave->Release();
		}
		CoUninitialize();
	}
}
