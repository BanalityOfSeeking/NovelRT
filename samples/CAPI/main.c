#include <stdio.h>
#include <stdint.h>
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.Interop/NovelRTNovelRunner.h"
#include "NovelRT.Interop/Input/NovelRTInteractionService.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/Timing/NovelRTStepTimer.h"
#include "NovelRT.Interop/Utilities/NovelRTEvents.h"

const char* error = " ";
NovelRTResult res = NOVELRT_SUCCESS;
NovelRTBool booleanResult = NOVELRT_TRUE;
NovelRTAudioService audio = NULL;
NovelRTInteractionService input = NULL;
NovelRTStepTimer timer = NULL;
NovelRTUpdateEventWithTimestamp updateEvent = NULL;

void inputTest(NovelRTTimestamp delta) {    
    NovelRTKeyStateFrameChangeLog in = NULL;
    res = NovelRT_InteractionService_getKeyState(input, W, &in, &error);
    if (res == NOVELRT_SUCCESS) {
        if (NovelRT_KeyStateFrameChangeLog_compareKeyState(KeyDown, in) == NOVELRT_TRUE) {
            fprintf(stdout, "W was pressed! \r\n");
            float vn = NovelRT_Timestamp_getSecondsFloat(delta);
            fprintf(stdout, "Timestamp: %f \r\n", vn);
        }
    }
    else {
        fprintf(stderr, error);
    }
}

void timerTest(NovelRTTimestamp delta) {
    uint32_t fps = 0;
    res = NovelRT_StepTimer_getFramesPerSecond(timer, &fps, &error);
    NovelRT_Timestamp_getSecondsFloat(delta);
    if (res == NOVELRT_SUCCESS) {
        fprintf(stdout, "FPS: %f \n", (double)(fps));
    }
}

int main() {
    
    NovelRTNovelRunner runner = NovelRT_NovelRunner_create(0);
    
    res = NovelRT_NovelRunner_getAudioService(runner, &audio, &error);
    if (res == NOVELRT_FAILURE) {
        fprintf(stderr, "Error getting AudioService:");
        fprintf(stderr, error);
        return -1;
    }
    else {
        res = NovelRT_AudioService_initialiseAudio(audio, &booleanResult, &error);
        if (res == NOVELRT_SUCCESS) {
            fprintf(stdout, "\nInitialised Audio from C API!\n");
        }
        else {
            fprintf(stderr, "Error initialising Audio:");
            fprintf(stderr, error);
        }   
    }

    res = NovelRT_NovelRunner_getInteractionService(runner, &input, &error);
    if (res == NOVELRT_FAILURE) {
        fprintf(stderr, "Error getting InteractionService:");
        fprintf(stderr, error);
        return -1;
    }
    else {
       fprintf(stdout, "\nInitialised Input from C API!\n");
    }

    res = NovelRT_StepTimer_create(60.0, 0.1, &timer, &error);
    res = NovelRT_Events_getNovelRunnerUpdateEvent(runner, &updateEvent, &error);

    NovelRT_StepTimer_tick(timer, updateEvent, &error);
    
    NovelRT_NovelRunner_addUpdate(runner, &inputTest, &error);
    NovelRT_NovelRunner_addUpdate(runner, &timerTest, &error);

    NovelRT_NovelRunner_runNovel(runner, &error);

    return 0;
}

