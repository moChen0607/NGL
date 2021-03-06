#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/cast.h>

#include "NGLInit.h"
namespace py = pybind11;
namespace ngl
{
  void pyInitNGLInit(py::module & m)
  {
    py::class_<NGLInit, std::unique_ptr<NGLInit, py::nodelete>>(m, "NGLInit")
        .def_static("instance",&NGLInit::instance)
        .def("setCommunicationMode",&NGLInit::setCommunicationMode);


    py::enum_<CommunicationMode>(m, "CommunicationMode")
           .value("NULLCONSUMER",CommunicationMode::NULLCONSUMER )
           .value("STDOUT",CommunicationMode::STDOUT )
           .value("STDERR",CommunicationMode::STDERR )
           .value("FILE",CommunicationMode::FILE );

  }

}
