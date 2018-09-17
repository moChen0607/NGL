/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "NGLInit.h"
#include "ShaderLib.h"
#include "VAOPrimitives.h"
#include "VAOFactory.h"
#include "SimpleVAO.h"
#include "MultiBufferVAO.h"
#include "SimpleIndexVAO.h"
#include <string>
#include <thread>
#include <chrono>

#if defined(LINUX) || defined(WIN32)
  #include <cstdlib>
#endif
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLInit.cpp
/// @brief implementation files for NGLInit class
//----------------------------------------------------------------------------------------------------------------------


namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------

void NGLInit::setCommunicationMode(ngl::CommunicationMode _mode)
{
  switch (_mode)
  {
    case CommunicationMode::STDERR : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::STDERR)); break;
    case CommunicationMode::STDOUT : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::STDOUT)); break;
    case CommunicationMode::NULLCONSUMER : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::NULLCONSUMER)); break;
    case CommunicationMode::FILE : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::FILE)); break;
    case CommunicationMode::NAMEDPIPE : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::NAMEDPIPE)); break;
    case CommunicationMode::SHAREDMEMORY : msg.reset(new  NGLMessage(NGLMessage::Mode::SERVER,CommunicationMode::SHAREDMEMORY)); break;
    case CommunicationMode::UDP : break;
    case CommunicationMode::TCPIP : break;
  }
}
NGLInit::NGLInit()
{
  //setCommunicationMode(CommunicationMode::STDERR);
#if defined(USINGIOS_) || !defined(__APPLE__)

  if (gl3wInit())
  {
     std::cerr<<"failed to initialize OpenGL\n";
     exit(EXIT_FAILURE);
  }
  if (!gl3wIsSupported(4, 1))
  {
    std::cerr<<"To run these demos you need a modern OpenGL Version\n";
    std::cerr<<"The lowest level OpenGL we support is 4.1\n";
    std::cerr<<"It could be you don't have the correct drivers installed\n";
    std::cerr<<"Or if linux on a laptop it could be using the intel driver and not the GPU\n";
    std::cerr<<"for more info contact Jon\n";
    exit(EXIT_FAILURE);
  }
#endif
  msg=std::make_unique<NGLMessage>(NGLMessage(NGLMessage::Mode::CLIENTSERVER,CommunicationMode::STDERR));

  msg->startMessageConsumer();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  msg->addMessage("NGL configured with ",Colours::NORMAL,TimeFormat::TIME);
  msg->addMessage(fmt::format("OpenGL {0}",glGetString(GL_VERSION)));
  msg->addMessage(fmt::format("GLSL version {0}",glGetString(GL_SHADING_LANGUAGE_VERSION)));


  VAOFactory::registerVAOCreator(simpleVAO,SimpleVAO::create);
  VAOFactory::registerVAOCreator(multiBufferVAO,MultiBufferVAO::create);
  VAOFactory::registerVAOCreator(simpleIndexVAO,SimpleIndexVAO::create);
}

//----------------------------------------------------------------------------------------------------------------------
NGLInit::~NGLInit()
{
  msg->stopMessageConsumer();
}


} // end of ngl namespace




