
set(Log_DIR Log)
build_library(Log)

set(Math_DIR Math)
build_library(Math)

set(Model_DIR Model)
build_library(Model)

set(CollisionDetection_DIR CollisionDetection)
build_library(CollisionDetection)

set(TinyXML_DIR ExternalSource/TinyXml2)
build_library(TinyXML)

set(Configure_DIR Configure)
build_library(Configure Log TinyXML)