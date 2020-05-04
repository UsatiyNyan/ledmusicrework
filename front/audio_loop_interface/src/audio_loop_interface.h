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
        size_t buf_size = 0);
    ~AudioLoopInterface() override;

 public slots:
    void on_start_capture(const pa::Device &audio_device);
    void on_set_params(const clr::RGBParameters &prms);

 private:
    loop::LockFreeContainer &_container;
    loop::AudioTfLoop *_audio_tf_loop = nullptr;
    size_t _size;
};

#endif //LED_PLAYER_FRONT_AUDIO_LOOP_INTERFACE_SRC_AUDIO_LOOP_INTERFACE_H_
