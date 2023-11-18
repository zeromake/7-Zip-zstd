#include <stdio.h>
#include <string.h>
#include <string>

#include "CPP/Common/Common.h"
#include "CPP/Common/MyString.h"
#include "CPP/7zip/Archive/IArchive.h"
#include "CPP/7zip/Common/FileStreams.h"
#include "CPP/7zip/IPassword.h"
#include "CPP/Windows/PropVariant.h"

#include "guids.h"
#include "register.hpp"

STDAPI CreateArchiver(const GUID *clsid, const GUID *iid, void **outObject);
STDAPI GetHandlerProperty2(UInt32 formatIndex, PROPID propID, PROPVARIANT *value);
STDAPI GetHandlerProperty(PROPID propID, PROPVARIANT *value);
STDAPI GetNumberOfFormats(UINT32 *numFormats);
STDAPI GetIsArc(UInt32 formatIndex, Func_IsArc *isArc);
void registerGenerateTable();

static void panic(const char* msg) {
  printf("%s\n", msg);
  abort();
}

class CArchiveOpenCallback:
  public IArchiveOpenCallback,
  public ICryptoGetTextPassword,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

  STDMETHOD(SetTotal)(const UInt64 *files, const UInt64 *bytes);
  STDMETHOD(SetCompleted)(const UInt64 *files, const UInt64 *bytes);

  STDMETHOD(CryptoGetTextPassword)(BSTR *password);

  bool PasswordIsDefined;
  UString Password;

  CArchiveOpenCallback() : PasswordIsDefined(false) {}
};

STDMETHODIMP CArchiveOpenCallback::SetTotal(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
  return S_OK;
}

STDMETHODIMP CArchiveOpenCallback::SetCompleted(const UInt64 * /* files */, const UInt64 * /* bytes */)
{
  return S_OK;
}
  
STDMETHODIMP CArchiveOpenCallback::CryptoGetTextPassword(BSTR *password)
{
  if (!PasswordIsDefined)
  {
    // You can ask real password here from user
    // Password = GetPassword(OutStream);
    // PasswordIsDefined = true;
    return E_ABORT;
  }
  return StringToBstr(Password, password);
}

int main(int argc, char *argv[]) {
  NArchive::RegisterAll();
  NWindows::NCOM::CPropVariant id;
  GetHandlerProperty(NArchive::NHandlerPropID::kClassID, (PROPVARIANT*)&id);
  IInArchive *archiver = NULL;
  CreateArchiver(id.puuid, &IID_IInArchive, (void**)&archiver);
  CInFileStream *archiveStream = new CInFileStream;
  if (!archiveStream->Open(std::move(FString(argv[1])))) panic("open error");
  UInt64 size;
  archiveStream->GetLength(size);
  printf("GetLength: %ld \n", size);
  CMyComPtr<IInStream> inStream(archiveStream);
  const UInt64 scanSize = 0;
  CArchiveOpenCallback *openCallbackSpec = new CArchiveOpenCallback;
  CMyComPtr<IArchiveOpenCallback> openCallback(openCallbackSpec);
  openCallbackSpec->PasswordIsDefined = false;
  // openCallbackSpec->Password = NULL;
  if (archiver->Open(inStream, &scanSize, openCallback) != S_OK) panic("archiver open error");
  UINT32 NumberOfItems = 0;
  if (archiver->GetNumberOfItems(&NumberOfItems) != S_OK) panic("GetNumberOfItems error");
  printf("GetNumberOfItems: %u\n", NumberOfItems);
  NWindows::NCOM::CPropVariant itemName;
  for (size_t i = 0; i < NumberOfItems; i++) {
    archiver->GetProperty(i, kpidPath, &itemName);
    printf("item %zd => %s\n", i, fs2fas(itemName.bstrVal).GetBuf());
  }
}
