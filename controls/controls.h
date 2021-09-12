#ifndef CONTROLS_H
#define CONTROLS_H

#include "core/control.h"
#include "imagecontrol.h"
#include "videocontrol.h"
#include "strokecontrol.h"
#include "webcontrol.h"
#include "pptxcontrol.h"
#include "docxcontrol.h"
#include "textcontrol.h"
#include "textinputcontrol.h"

#include <qexport.h>

REGISTER_CONTROL(ImageControl, "image,bmp,gif,jpg,jpeg,png,svg")

#ifdef QT_DEBUG
REGISTER_CONTROL(VideoControl, "video,mp4,wmv,webm,ts,flv,m3u8,asf,avi,"
                               "audio,mp3,wma,wav,m4a,"
                                "rtsp,rtmp,rtp")
REGISTER_CONTROL(StrokeControl, "glstroke")
#endif
REGISTER_CONTROL(WebControl, "htm,html,http,https,chrome,swf")
REGISTER_CONTROL(TextControl, "text,txt,js,cpp,h,qss,css")
REGISTER_CONTROL(TextInputControl, "textinput")

#ifdef WIN32
REGISTER_CONTROL(PptxControl, "ppt,pptx")
# ifdef QT_DEBUG
REGISTER_CONTROL(DocxControl, "doc,docx")
# endif
#endif


#endif // CONTROLS_H
