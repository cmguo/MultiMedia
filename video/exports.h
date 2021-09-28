#ifndef VIDEO_EXPORTS_H
#define VIDEO_EXPORTS_H

#include "avmediaplayerbridge.h"
#include "qtmediaplayerbridge.h"
//#include "videocontroller.h"

#include <qexport.h>

static QExport<QtMediaPlayerBridge, MediaPlayerBridge> export_qt(QPart::shared);
static QExport<AVMediaPlayerBridge, MediaPlayerBridge> export_av(QPart::shared);
//static QExport<VideoController> export_video_controller(QPart::nonshared);

#endif // VIDEO_EXPORTS_H
