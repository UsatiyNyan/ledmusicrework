//
// Created by kira on 04.05.2020.
//

#ifndef LED_PLAYER_FRONT_AUDIO_LOOP_INTERFACE_SRC_AUDIO_LOOP_INTERFACE_H_
#define LED_PLAYER_FRONT_AUDIO_LOOP_INTERFACE_SRC_AUDIO_LOOP_INTERFACE_H_

#include <QWidget>

#include "audio_tf_loop.h"


class AudioLoopInterface : public QWidget {
    Q_OBJECT

 public:
    explicit AudioLoopInterface(QWidget *parent = nullptr,
        loop::LockFreeContainer *container = nullptr,
        clr::RGBParameters *prms = nullptr,
        size_t buf_size = 0);
    ~AudioLoopInterface() override;

 public slots:
    void on_start_capture(const pa::Device &audio_device);
    void on_rgb_settings(const clr::RGBParameters &prms);

 private:
    loop::LockFreeContainer *_container = nullptr;
    loop::AudioTfLoop *_audio_tf_loop = nullptr;
    clr::RGBParameters *_rgb_parameters = nullptr;
    size_t _size;
};

#endif //LED_PLAYER_FRONT_AUDIO_LOOP_INTERFACE_SRC_AUDIO_LOOP_INTERFACE_H_
