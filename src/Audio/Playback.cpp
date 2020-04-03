//
// Created by samt on 01/04/2020.
//

#include "Playback.h"


// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
          double streamTime, RtAudioStreamStatus status, void *dataPointer )
{
    SineWave *sine = (SineWave *) dataPointer;
    register StkFloat *samples = (StkFloat *) outputBuffer;
    for ( unsigned int i=0; i<nBufferFrames; i++ )
        *samples++ = sine->tick();
    return 0;
}


void PlaybackEngine::cleanup(){

}

void PlaybackEngine::play() {
    // Set the global sample rate before creating class instances.
    Stk::setSampleRate(44100.0);
    SineWave sine;
    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = (sizeof(StkFloat) == 8) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;
    try {
        dac.openStream(&parameters, NULL, format, (unsigned int) Stk::sampleRate(), &bufferFrames, &tick,
                       (void *) &sine);
    }
    catch (RtAudioError &error) {
        error.printMessage();
        cleanup();
        return;
    }
    sine.setFrequency(440.0);
    try {
        dac.startStream();
    }
    catch (RtAudioError &error) {
        error.printMessage();
        cleanup();
        return;
    }
}

void PlaybackEngine::stop() {
    try {
        dac.closeStream();
    }
    catch (RtAudioError &error) {
        error.printMessage();
    }
}

int PlaybackEngine::getDeviceCount() {
    return dac.getDeviceCount();
}

void PlaybackEngine::printDeviceInfo() {
    RtAudio *audioTemp = NULL;
    audioTemp = new RtAudio();
    unsigned int devices = audioTemp->getDeviceCount();
    RtAudio::DeviceInfo info;

    for (int i=0;i<devices;i++){
        info = audioTemp->getDeviceInfo(i);
        std::cout<<"default input: "<<audioTemp->getDefaultInputDevice()<<std::endl;
        std::cout<<"default output: "<<audioTemp->getDefaultOutputDevice()<<std::endl;
        if (info.probed ==true){
            std::cout<<"----------------------------- Device "<<i<<" ---------------------------"<<std::endl;
            if (info.isDefaultInput)
                std::cout << "--Default Input"<<std::endl;
            if (info.isDefaultOutput)
                std::cout << "--Default Output"<<std::endl;
            std::cout << "Name = " << info.name << '\n';
            std::cout << "Max Input Channels = " << info.inputChannels << '\n';
            std::cout << "Max Output Channels = " << info.outputChannels << '\n';
            std::cout << "Max Duplex Channels = " << info.duplexChannels << '\n';
        }
    }
    delete audioTemp;
    audioTemp = NULL;
}