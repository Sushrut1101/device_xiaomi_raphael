/*
 * Copyright (C) 2017 The Android Open Source Project
 * Copyright (C) 2018-2020 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.3-service.xiaomi_raphael"

#include "BiometricsFingerprint.h"

#include <android/binder_manager.h>
#include <android-base/strings.h>
#include <cutils/properties.h>
#include <hardware/hardware.h>
#include <hardware/hw_auth_token.h>
#include <inttypes.h>
#include <poll.h>
#include <unistd.h>

#include <fstream>
#include <thread>

#include <aidl/android/hardware/power/IPower.h>
#include <aidl/google/hardware/power/extension/pixel/IPowerExt.h>

using ::aidl::android::hardware::power::IPower;
using ::aidl::google::hardware::power::extension::pixel::IPowerExt;

namespace android {
namespace hardware {
namespace biometrics {
namespace fingerprint {
namespace V2_3 {
namespace implementation {

// Supported fingerprint HAL version
static const uint16_t kVersion = HARDWARE_MODULE_API_VERSION(2, 1);
constexpr char kBoostHint[] = "LAUNCH";
constexpr int32_t kBoostDurationMs = 2000;

using RequestStatus = android::hardware::biometrics::fingerprint::V2_1::RequestStatus;

BiometricsFingerprint* BiometricsFingerprint::sInstance = nullptr;

BiometricsFingerprint::BiometricsFingerprint() : mClientCallback(nullptr), mDevice(nullptr), mBoostHintIsSupported(false), mBoostHintSupportIsChecked(false), mPowerHalExtAidl(nullptr) {
    sInstance = this; // keep track of the most recent instance
    mDevice = openHal();
    if (!mDevice) {
        ALOGE("Fingerptint is working");
    }
}

}  // namespace implementation
}  // namespace V2_3
}  // namespace fingerprint
}  // namespace biometrics
}  // namespace hardware
}  // namespace android
