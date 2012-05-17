/*****************************************************************************
 * httplivestreambuffer.cpp
 * MythTV
 *
 * Created by Jean-Yves Avenard on 6/05/12.
 * Copyright (c) 2012 Bubblestuff Pty Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef MythXCode_hlsbuffer_h
#define MythXCode_hlsbuffer_h

#include "mythcorecontext.h"
#include "ringbuffer.h"

extern "C" {
#include "libavformat/avformat.h"
#include "libavformat/url.h"
}

class MythDownloadManager;
class HLSStream;
class HLSSegment;
class StreamWorker;
class PlaylistWorker;
class HLSPlayback;

typedef QList<HLSStream*> StreamsList;

class HLSRingBuffer : public RingBuffer
{
public:
    HLSRingBuffer(const QString &lfilename);
    virtual ~HLSRingBuffer();

    virtual bool IsOpen(void) const;
    virtual long long GetReadPosition(void) const;
    virtual bool OpenFile(const QString &lfilename,
                          uint retry_ms = kDefaultOpenTimeout);
    virtual long long Seek(long long pos, int whence, bool has_lock);
    virtual long long GetRealFileSize(void) const;
    virtual bool IsStreamed(void)       { return true;   }
    virtual bool IsSeekingAllowed(void);
    virtual bool IsBookmarkAllowed(void) { return true; }
    static bool IsHTTPLiveStreaming(QByteArray *s);
    static bool TestForHTTPLiveStreaming(QString &filename);
    bool SaveToDisk(QString filename);

protected:
    virtual int safe_read(void *data, uint i_read);

private:
    void FreeStreamsList(QList<HLSStream*> *streams);
    HLSStream *GetStreamForSegment(int segid);
    HLSStream *GetStream(const int wanted, const StreamsList *streams = NULL) const;
    HLSStream *GetFirstStream(const StreamsList *streams = NULL);
    HLSStream *GetLastStream(const StreamsList *streams = NULL);
    HLSStream *FindStream(const HLSStream *hls_new, const StreamsList *streams = NULL);
    HLSStream *CurrentStream(void);
    int BandwidthAdaptation(int progid, uint64_t &bandwidth);
    QString ParseAttributes(QString &line, const char *attr);
    int ParseSegmentInformation(HLSStream *hls, QString &line,
                                int &duration, QString &title);
    int ParseTargetDuration(HLSStream *hls, QString &line);
    HLSStream *ParseStreamInformation(QString &line, QString &uri);
    int ParseMediaSequence(HLSStream *hls, QString &line);
    int ParseKey(HLSStream *hls, QString &line);
    int ParseProgramDateTime(HLSStream *hls, QString &line);
    int ParseAllowCache(HLSStream *hls, QString &line);
    int ParseVersion(QString &line, int &version);
    int ParseEndList(HLSStream *hls);
    int ParseDiscontinuity(HLSStream *hls, QString &line);
    int ParseM3U8(const QByteArray *buffer, StreamsList *streams = NULL);
    int Prefetch(int count);
    void SanityCheck(HLSSegment *segment);
    HLSSegment *GetSegment(int segnum, int timeout = 1000);
    int NumSegments(void) const;
    int ChooseSegment(int stream);
    int64_t SizeMedia(void) const;
    int64_t CalculateOffset(int count, int64_t *max = NULL, int *segnum = NULL);

    // private member variables
    QString             m_m3u8;     // M3U8 url
    QByteArray          m_peeked;

    HLSPlayback       *m_playback;

    /* state */
    StreamsList         m_streams;  // bandwidth adaptation
    mutable QMutex      m_lock;     // protect general class members
    bool                m_cache;    // can cache files
    bool                m_meta;     // meta playlist
    bool                m_live;     // live stream? or vod?
    bool                m_falsevod; // stream was incorrectly detected a VOD
    bool                m_error;    // parsing error
    bool                m_aesmsg;   // only print one time that the media is encrypted
    friend class StreamWorker;
    StreamWorker       *m_streamworker;
    friend class PlaylistWorker;
    PlaylistWorker     *m_playlistworker;
};

#endif
