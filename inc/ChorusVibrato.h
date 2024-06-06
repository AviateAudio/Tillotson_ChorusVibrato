/*
 * Company: Tillotson
 * Effect Name: Hammond Chorus Vibrato
 * Description: A circuit simulation of the Hammond Scanner Vibrato. Effect by Mark Tillotson.
 *
 * This file was auto-generated by Aviate Audio Effect Creator for the Multiverse.
 */
#pragma once

#include <Audio.h>
#include <arm_math.h>
#include "Aviate/AudioEffectWrapper.h"

//!s - START_USER_INCLUDES - put your #includes below this line before the matching END
//!e - END_USER_INCLUDES

namespace Tillotson_ChorusVibrato {

//!s - START_USER_EFFECT_TYPES - put your effect types below this line before the matching END
//!e - END_USER_EFFECT_TYPES

class ChorusVibrato : public AudioStream, public Aviate::AudioEffectWrapper {
public:
    static constexpr unsigned NUM_INPUTS  = 1;
    static constexpr unsigned NUM_OUTPUTS = 1;

    // List of effect control names
    enum {
        Bypass_e = 0,
        Volume_e = 1,
        Mode_e = 2,
        Depth_e = 3,
        Mix_e = 4,
        LED_e = 5,
        NUM_CONTROLS
    };

    //!s - START_USER_CLASS_TYPES - put your custom class types below this line before the matching END
    //!e - END_USER_CLASS_TYPES

    ChorusVibrato();

    //!s - START_USER_CONSTRUCTORS - put your custom constructors below this line before the matching END
    //!e - END_USER_CONSTRUCTORS

    virtual ~ChorusVibrato();

    // Standard EFX interface functions - do not change these declaration
    virtual void update(); // main audio processing loop function
    void mapMidiControl(int parameter, int midiCC, int midiChannel = 0) override;
    void processMidi(int channel, int midiCC, int value) override;
    void setParam(int paramIndex, float paramValue) override;
    float getUserParamValue(int paramIndex, float normalizedParamValue);
    const char* getName() override;
    const uint8_t* getRblk() override;

    // control value set functions, must take floats between 0.0f and 1.0f - do not change these declarations
    void volume(float value) override;
    void mode(float value);
    void depth(float value);
    void mix(float value);
    void led(float value);

    //!s - START_USER_PUBLIC_MEMBERS - put your public members below this line before the matching END
    void bypass(bool byp) override;
    //!e - END_USER_PUBLIC_MEMBERS

private:
    audio_block_t *m_inputQueueArray[1]; // required by AudioStream base class, array size is num inputs
    int m_midiConfig[NUM_CONTROLS][2]; // stores the midi parameter mapping

    // m_bypass and m_volume are already provided by the base class AudioEffectWrapper or AudioEffectFloat
    float m_mode = 0.0f;
    float m_depth = 0.0f;
    float m_mix = 0.0f;
    float m_led = 0.0f;

    audio_block_t* m_basicInputCheck(audio_block_t* inputAudioBlock, unsigned outputChannel);

    //!s - START_USER_PRIVATE_MEMBERS - put your private members below this line before the matching END
    void init();
    float butterworth (float s) ;
    void simulate_lineunit (float s) ;
    void set_taps ();

    int SAMPS_PER_SEG = 0;
    float* crossfade = nullptr;

    bool m_initComplete = false;
    int scanner_ph ;  // scanner segment tracking
    int scanner_seg ;
    int tap, ntap ;

    //bool enabled ;    // configuration
    bool vibrato ;
    int _depth;

    float filtvals[2] ;  // butterworth coeffs

    float V[19] ;  // circuit state, node voltages/currents
    float I[18] ;
    float Vg, deltaVg ;
    float out[19] ;  // tap outputs
    //!e - END_USER_PRIVATE_MEMBERS

};

}
