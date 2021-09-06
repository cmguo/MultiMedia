#ifndef RESOURCES_H
#define RESOURCES_H

#include <core/resourceview.h>

REGISTER_COMMON_RESOURCE_TYPES(image, "image,bmp,gif,jpg,jpeg,png", {}, {}) // copyable
REGISTER_COMMON_RESOURCE_TYPES(text, "text,txt,js,cpp,h,qss,css", {}, ResourceView::CanCopy)
REGISTER_COMMON_RESOURCE_TYPES(doc, "ppt,pptx,html,htm,swf", {}, ResourceView::CanCopy)
REGISTER_COMMON_RESOURCE_TYPES(video, "video,mp4,wmv,ts,flv,m3u8,asf,avi,"
                                      "audio,mp3,wma,wav,"
                                      "rtsp,rtmp,rtp", {}, {ResourceView::CanCopy})

#endif // RESOURCES_H
