#pragma once

#ifndef USE_DLL_EXPORT
namespace NArchive {
    namespace NApfs {
        void registerArc();
    }
    namespace NApm {
        void registerArc();
    }
    namespace NAr {
        void registerArc();
    }
    namespace NArj {
        void registerArc();
    }
    namespace NBase64 {
        void registerArc();
    }
    namespace NBROTLI {
        void registerArc();
    }
    namespace NBz2 {
        void registerArc();
    }
    namespace NCom {
        void registerArc();
    }
    namespace NCpio {
        void registerArc();
    }
    namespace NCramfs {
        void registerArc();
    }
    namespace NDmg {
        void registerArc();
    }
    namespace NElf {
        void registerArc();
    }
    namespace NExt {
        void registerArc();
    }
    namespace NFat {
        void registerArc();
    }
    namespace NFlv {
        void registerArc();
    }
    namespace NFat {
        void registerArc();
    }
    namespace NGpt {
        void registerArc();
    }
    namespace NGz {
        void registerArc();
    }
    namespace NHfs {
        void registerArc();
    }
    namespace NIhex {
        void registerArc();
    }
    namespace NLIZARD {
        void registerArc();
    }
    namespace NLp {
        void registerArc();
    }
    namespace NLZ4 {
        void registerArc();
    }
    namespace NLZ5 {
        void registerArc();
    }
    namespace NLz {
        void registerArc();
    }
    namespace NLzh {
        void registerArc();
    }
    namespace NLzma::NLzmaAr {
        void registerArc();
    }
    namespace NLzma::NLzma86Ar {
        void registerArc();
    }
    namespace NMacho {
        void registerArc();
    }
    namespace NMbr {
        void registerArc();
    }
    namespace NMslz {
        void registerArc();
    }
    namespace NMub::NBe {
        void registerArc();
    }
    namespace Ntfs {
        void registerArc();
    }
    namespace NPe {
        void registerArc();
    }
    namespace NCoff {
        void registerArc();
    }
    namespace NTe {
        void registerArc();
    }
    namespace NPpmd {
        void registerArc();
    }
    namespace NQcow {
        void registerArc();
    }
    namespace NRpm {
        void registerArc();
    }
    namespace NSparse {
        void registerArc();
    }
    namespace NSplit {
        void registerArc();
    }
    namespace NSquashfs {
        void registerArc();
    }
    namespace NSwfc {
        void registerArc();
    }
    namespace NSwf {
        void registerArc();
    }
    namespace NUefi::UEFIc {
        void registerArc();
    }
    namespace NUefi::UEFIf {
        void registerArc();
    }
    namespace NVdi {
        void registerArc();
    }
    namespace NVhd {
        void registerArc();
    }
    namespace NVhdx {
        void registerArc();
    }
    namespace NVmdk {
        void registerArc();
    }
    namespace NVmdk {
        void registerArc();
    }
    namespace NXar {
        void registerArc();
    }
    namespace NXz {
        void registerArc();
    }
    namespace NZ {
        void registerArc();
    }
    namespace NZSTD {
        void registerArc();
    }
    namespace N7z {
        void registerArc();
    }
    namespace NCab {
        void registerArc();
    }
    namespace NChm {
        namespace NChm {
            void registerArc();
        }
        namespace NHxs {
            void registerArc();
        }
    }
    namespace NIso {
        void registerArc();
    }
    namespace NNsis {
        void registerArc();
    }
    namespace NRar5 {
        void registerArc();
    }
    namespace NRar {
        void registerArc();
    }
    namespace NTar {
        void registerArc();
    }
    namespace NUdf {
        void registerArc();
    }
    namespace NWim {
        void registerArc();
    }
    namespace NZip {
        void registerArc();
    }
}


void registerCodecBROTLI();
void registerCodecFLZMA2();
void registerCodecLIZARD();
void registerCodecLZ4();
void registerCodecLZ5();
void registerCodecZSTD();
namespace NCompress {
    void registerCodecCopy();
    void registerCodecRar();
    namespace NBcj2 {
        void registerCodecBCJ2();
    }
    namespace NBranch {
        void registerCodecBranch();
    }
    namespace NByteSwap {
        void registerCodecByteSwap();
    }
    namespace NBZip2 {
        void registerCodecBZip2();
    }
    namespace NDeflate {
        void registerCodecDeflate64();
        void registerCodecDeflate();
    }
    namespace NLzma2 {
        void registerCodecLZMA2();
    }
    namespace NLzma {
        void registerCodecLZMA();
    }
    namespace NPpmd {
        void registerCodecPPMD();
    }
}

void regHasherCBLAKE3Hasher();
void regHasherCCksumHasher();
void regHasherCCrcHasher();
void regHasherCMD2Hasher();
void regHasherCMD4Hasher();
void regHasherCMD5Hasher();
void regHasherCSha1Hasher();
void regHasherCSHA3_256Hasher();
void regHasherCSHA3_384Hasher();
void regHasherCSha1Hasher();
void regHasherCSHA3_512Hasher();
void regHasherCSha256Hasher();
void regHasherCSHA384Hasher();
void regHasherCSHA512Hasher();
void regHasherCXXH32Hasher();
void regHasherCXXH64Hasher();
void regHasherCXzCrc64Hasher();

void registerCCRCTableInit();

namespace NArchive {
    void RegisterAllCodec() {
        registerCodecBROTLI();
        registerCodecFLZMA2();
        registerCodecLIZARD();
        registerCodecLZ4();
        registerCodecLZ5();
        registerCodecZSTD();
        NCompress::registerCodecCopy();
        NCompress::registerCodecRar();

        NCompress::NBcj2::registerCodecBCJ2();
        NCompress::NBranch::registerCodecBranch();
        NCompress::NByteSwap::registerCodecByteSwap();
        NCompress::NBZip2::registerCodecBZip2();
        NCompress::NDeflate::registerCodecDeflate();
        NCompress::NDeflate::registerCodecDeflate64();
        NCompress::NLzma::registerCodecLZMA();
        NCompress::NLzma2::registerCodecLZMA2();
        NCompress::NPpmd::registerCodecPPMD();
    }

    void RegisterAllArc() {
        // NArchive::NApfs::registerArc();
        // NArchive::NApm::registerArc();
        // NArchive::NAr::registerArc();
        // NArchive::NArj::registerArc();
        // NArchive::NBase64::registerArc();
        NArchive::NBROTLI::registerArc();
        NArchive::NBz2::registerArc();
        // NArchive::NCom::registerArc();
        NArchive::NCpio::registerArc();
        // NArchive::NCramfs::registerArc();
        NArchive::NDmg::registerArc();
        // NArchive::NElf::registerArc();
        // NArchive::NExt::registerArc();
        // NArchive::NFat::registerArc();
        // NArchive::NFlv::registerArc();
        // NArchive::NFat::registerArc();
        // NArchive::NGpt::registerArc();
        NArchive::NGz::registerArc();
        // NArchive::NHfs::registerArc();
        // NArchive::NIhex::registerArc();
        NArchive::NLIZARD::registerArc();
        // NArchive::NLp::registerArc();
        NArchive::NLZ4::registerArc();
        NArchive::NLZ5::registerArc();
        // NArchive::NLz::registerArc();
        // NArchive::NLzh::registerArc();
        NArchive::NLzma::NLzmaAr::registerArc();
        NArchive::NLzma::NLzma86Ar::registerArc();
        // NArchive::NMacho::registerArc();
        // NArchive::NMbr::registerArc();
        // NArchive::NMslz::registerArc();
        // NArchive::NMub::NBe::registerArc();
        // NArchive::Ntfs::registerArc();
        // NArchive::NPe::registerArc();
        // NArchive::NCoff::registerArc();
        // NArchive::NTe::registerArc();
        // NArchive::NPpmd::registerArc();
        // NArchive::NQcow::registerArc();
        // NArchive::NRpm::registerArc();
        // NArchive::NSparse::registerArc();
        // NArchive::NSplit::registerArc();
        // NArchive::NSquashfs::registerArc();
        // NArchive::NSwfc::registerArc();
        // NArchive::NSwf::registerArc();
        // NArchive::NUefi::UEFIc::registerArc();
        // NArchive::NUefi::UEFIf::registerArc();
        // NArchive::NVdi::registerArc();
        // NArchive::NVhd::registerArc();
        // NArchive::NVhdx::registerArc();
        // NArchive::NVmdk::registerArc();
        // NArchive::NVmdk::registerArc();
        // NArchive::NXar::registerArc();
        NArchive::NXz::registerArc();
        // NArchive::NZ::registerArc();
        NArchive::NZSTD::registerArc();
        NArchive::N7z::registerArc();
        NArchive::NCab::registerArc();
        // NArchive::NChm::NChm::registerArc();
        // NArchive::NChm::NHxs::registerArc();
        NArchive::NIso::registerArc();
        // NArchive::NNsis::registerArc();
        NArchive::NRar5::registerArc();
        NArchive::NRar::registerArc();
        NArchive::NTar::registerArc();
        // NArchive::NUdf::registerArc();
        // NArchive::NWim::registerArc();
        NArchive::NZip::registerArc();
    }

    void RegisterAllHasher() {
        regHasherCBLAKE3Hasher();
        regHasherCCksumHasher();
        regHasherCCrcHasher();
        regHasherCMD2Hasher();
        regHasherCMD4Hasher();
        regHasherCMD5Hasher();
        regHasherCSha1Hasher();
        regHasherCSHA3_256Hasher();
        regHasherCSHA3_384Hasher();
        regHasherCSha1Hasher();
        regHasherCSHA3_512Hasher();
        regHasherCSha256Hasher();
        regHasherCSHA384Hasher();
        regHasherCSHA512Hasher();
        regHasherCXXH32Hasher();
        regHasherCXXH64Hasher();
        regHasherCXzCrc64Hasher();
    }
    void RegisterAll() {
        RegisterAllCodec();
        RegisterAllArc();
        RegisterAllHasher();
        registerCCRCTableInit();
    }
}
#else
namespace NArchive {
    void RegisterAll() {}
}
#endif
