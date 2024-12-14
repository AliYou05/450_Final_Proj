#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

static const char *TAG = "VoiceAnnouncement";

// Event group for signaling
static EventGroupHandle_t voice_event_group;
#define VOICE_EVENT_LIGHT_CHANGED (1 << 0)

// Shared variable for brightness level
static uint8_t current_brightness = 0;

// Function to simulate voice feedback
void play_voice_feedback(uint8_t brightness) {
    ESP_LOGI(TAG, "Announcing brightness: %d%%", brightness);

}

void voice_announcement_task(void *arg) {
    while (1) {
        // Wait for the lighting change event
        xEventGroupWaitBits(voice_event_group, VOICE_EVENT_LIGHT_CHANGED, pdTRUE, pdFALSE, portMAX_DELAY);
        
        // Access the current brightness and play voice feedback
        play_voice_feedback(current_brightness);
    }
}

void init_voice_announcement() {
    voice_event_group = xEventGroupCreate();
    xTaskCreate(voice_announcement_task, "VoiceTask", 2048, NULL, 5, NULL);
}

void notify_brightness_change(uint8_t brightness) {
    current_brightness = brightness;
    xEventGroupSetBits(voice_event_group, VOICE_EVENT_LIGHT_CHANGED);
}
