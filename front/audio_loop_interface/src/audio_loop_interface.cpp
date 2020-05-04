//
// Created by kira on 04.05.2020.
//

#include "audio_loop_interface.h"


AudioLoopInterface::AudioLoopInterface(QWidget *parent,
                                       loop::LockFreeContainer *container,
                                       size_t buf_size)
                                       : QWidget(parent),
                                         _container(*container),
                                         _size(buf_size) {
}

AudioLoopInterface::~AudioLoopInterface() {
    delete _audio_tf_loop;
}

void AudioLoopInterface::on_start_capture(const pa::Device &audio_device) {
    delete _audio_tf_loop;
    _audio_tf_loop = new loop::AudioTfLoop(_container, audio_device, _size);
    _audio_tf_loop->run();
}

void AudioLoopInterface::on_set_params(const clr::RGBParameters &prms){
    _audio_tf_loop->set_params(prms);
}
