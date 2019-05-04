#include "chrome/utility/importer/importer_creator.h"
#define CreateImporterByType CreateImporterByType_ChromiumImpl
#include "../../../../../chrome/utility/importer/importer_creator.cc"
#undef CreateImporterByType

#include "onevn/utility/importer/onevn_importer.h"
#include "onevn/utility/importer/chrome_importer.h"
#include "onevn/utility/importer/firefox_importer.h"

namespace importer {

scoped_refptr<Importer> CreateImporterByType(ImporterType type) {
  switch (type) {
    case TYPE_FIREFOX:
      return new onevn::FirefoxImporter();
    case TYPE_CHROME:
      return new ChromeImporter();
    case TYPE_ONEVN:
      return new OneVNImporter();
    default:
      return CreateImporterByType_ChromiumImpl(type);
  }
}

}  // namespace importer
