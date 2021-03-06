/*
 * Copyright (c) 2005-2018, BearWare.dk
 * 
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Kirketoften 5
 * DK-8260 Viby J
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk SDK owned by
 * BearWare.dk. Use of this file, or its compiled unit, requires a
 * TeamTalk SDK License Key issued by BearWare.dk.
 *
 * The TeamTalk SDK License Agreement along with its Terms and
 * Conditions are outlined in the file License.txt included with the
 * TeamTalk SDK distribution.
 *
 */

#ifndef WINDOWS_MEDIA_H
#define WINDOWS_MEDIA_H

#include <ace/Task.h>
#include <ace/Bound_Ptr.h>
#include <ace/Future.h>
#include <ace/Semaphore.h>

#include <codec/MediaStreamer.h>

bool GetDSMediaFileProp(const ACE_TString& filename, MediaFileProp& fileprop);

class DSWrapperThread : protected ACE_Task<ACE_MT_SYNCH>
                      , public MediaStreamer
{
public:
    DSWrapperThread(MediaStreamListener* listener);
    virtual ~DSWrapperThread();

    bool OpenFile(const MediaFileProp& in_prop,
                  const MediaStreamOutput& out_prop);

    bool StartStream();

    void Close();


private:
    int svc();
    int handle_timeout(const ACE_Time_Value &current_time, const void *act);

    typedef ACE_Future<bool> fileopen_t;
    fileopen_t m_open, m_start;
};

typedef ACE_Strong_Bound_Ptr< DSWrapperThread, ACE_Null_Mutex > dswrapper_t;


#endif
