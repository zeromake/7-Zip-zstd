#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

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

static void panic(const char *msg)
{
  printf("%s\n", msg);
  abort();
}

class CArchiveOpenCallback : public IArchiveOpenCallback,
                             public ICryptoGetTextPassword,
                             public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(ICryptoGetTextPassword)

  STDMETHOD(SetTotal)
  (const UInt64 *files, const UInt64 *bytes);
  STDMETHOD(SetCompleted)
  (const UInt64 *files, const UInt64 *bytes);

  STDMETHOD(CryptoGetTextPassword)
  (BSTR *password);

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

namespace zzip
{
  class COutMemStream : public ISequentialOutStream,
                        public CMyUnknownImp
  {
  public:
    MY_UNKNOWN_IMP1(ISequentialOutStream)
    COutMemStream(std::vector<BYTE> &out_buffer) : m_buffer(out_buffer){};
    ~COutMemStream(){};
    STDMETHOD(Write)
    (const void *data, UInt32 size, UInt32 *processedSize)
    {
      if (processedSize != nullptr)
      {
        *processedSize = 0;
      }
      if (data == NULL || size == 0)
      {
        return E_FAIL;
      }
      const BYTE *byte_data = static_cast<const BYTE *>(data);
      m_buffer.insert(m_buffer.end(), byte_data, byte_data + size);
      *processedSize = size;
      return S_OK;
    };

  private:
    std::vector<BYTE> &m_buffer;
  };

  class MemExtractCallback : public IArchiveExtractCallback,
                             public CMyUnknownImp
  {
  public:
    MY_UNKNOWN_IMP1(IArchiveExtractCallback)
    // IProgress
    STDMETHOD(SetTotal)
    (UInt64 size);
    STDMETHOD(SetCompleted)
    (const UInt64 *completeValue);
    // IArchiveExtractCallback
    STDMETHOD(GetStream)
    (UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode);
    STDMETHOD(PrepareOperation)
    (Int32 askExtractMode);
    STDMETHOD(SetOperationResult)
    (Int32 resultEOperationResult);
    MemExtractCallback(std::vector<BYTE> &buffer) : m_buffer(buffer){};
    virtual ~MemExtractCallback() = default;

  private:
    std::vector<BYTE> &m_buffer;
    CMyComPtr<ISequentialOutStream> m_outMemStream;
  };

  STDMETHODIMP MemExtractCallback::SetTotal(UInt64 size)
  {
    return S_OK;
  }
  STDMETHODIMP MemExtractCallback::SetCompleted(const UInt64 *completeValue)
  {
    return S_OK;
  }

  STDMETHODIMP MemExtractCallback::GetStream(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode)
  {
    CMyComPtr<ISequentialOutStream> outStreamLoc(new zzip::COutMemStream(m_buffer));
    m_outMemStream = outStreamLoc;
    *outStream = outStreamLoc.Detach();
    return S_OK;
  }
  STDMETHODIMP MemExtractCallback::PrepareOperation(Int32 askExtractMode)
  {
    return S_OK;
  }

  STDMETHODIMP MemExtractCallback::SetOperationResult(Int32 operationResult)
  {
    m_outMemStream.Release();
  }
}

int main(int argc, char *argv[])
{
  NArchive::RegisterAll();
  NWindows::NCOM::CPropVariant id;
  GetHandlerProperty(NArchive::NHandlerPropID::kClassID, (PROPVARIANT *)&id);
  IInArchive *archiver = NULL;
  GUID guid;
  memcpy(&guid, id.bstrVal, sizeof(GUID));
  CreateArchiver(&guid, &IID_IInArchive, (void **)&archiver);
  CInFileStream *archiveStream = new CInFileStream;
  if (!archiveStream->Open(fas2fs(argv[1])))
    panic("open error");
  UInt64 size;
  archiveStream->GetLength(size);
  printf("GetLength: %ld \n", size);
  CMyComPtr<IInStream> inStream(archiveStream);
  const UInt64 scanSize = 0;
  CArchiveOpenCallback *openCallbackSpec = new CArchiveOpenCallback;
  CMyComPtr<IArchiveOpenCallback> openCallback(openCallbackSpec);
  openCallbackSpec->PasswordIsDefined = false;
  // openCallbackSpec->Password = NULL;
  if (archiver->Open(inStream, &scanSize, openCallback) != S_OK)
    panic("archiver open error");
  UINT32 NumberOfItems = 0;
  if (archiver->GetNumberOfItems(&NumberOfItems) != S_OK)
    panic("GetNumberOfItems error");
  printf("GetNumberOfItems: %u\n", NumberOfItems);
  NWindows::NCOM::CPropVariant itemName;
  NWindows::NCOM::CPropVariant itemSize;
  NWindows::NCOM::CPropVariant itemIsDir;
  for (size_t i = 0; i < NumberOfItems; i++)
  {
    archiver->GetProperty(i, kpidIsDir, &itemIsDir);
    if (itemIsDir.boolVal)
    {
      continue;
    }
    archiver->GetProperty(i, kpidPath, &itemName);
    archiver->GetProperty(i, kpidSize, &itemSize);
    printf("item %zd => %s %ld\n", i, us2fs(itemName.bstrVal).GetBuf(), itemSize.uhVal.QuadPart);
  }
  const UInt32 indices[] = {2};
  std::vector<BYTE> buffer;
  buffer.reserve(256);
  CMyComPtr<zzip::MemExtractCallback> extractCallback = new zzip::MemExtractCallback(buffer);
  if (archiver->Extract(indices, 1, false, extractCallback) != S_OK)
    panic("Extract error");
  buffer[48] = '\0';
  printf("Extract: %s\n", buffer.data());
}
