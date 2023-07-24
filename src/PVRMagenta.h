/*
 *  Copyright (C) 2011-2021 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2011 Pulse-Eight (http://www.pulse-eight.com/)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include <string>
#include <vector>

#include <kodi/addon-instance/PVR.h>
#include "Settings.h"
#include "http/HttpClient.h"
#include "rapidjson/document.h"

static const std::string GUEST_URL = "https://slbedmfk11100.prod.sngtv.t-online.de:33428/";

struct MagentaCategory
{
  std::string name;
  std::string id;
};

struct MagentaChannel
{

  bool bRadio;
  bool bArchive;
  int iUniqueId;
  int mediaId;
  int iChannelNumber; //position
  std::string strChannelName;
  std::string strIconPath;
  std::string strStreamURL;
  std::vector<long> categories;
};

class ATTR_DLL_LOCAL CPVRMagenta : public kodi::addon::CAddonBase,
                                public kodi::addon::CInstancePVRClient
{
public:
  CPVRMagenta();
  ~CPVRMagenta() override;

  PVR_ERROR GetBackendName(std::string& name) override;
  PVR_ERROR GetBackendVersion(std::string& version) override;
  PVR_ERROR GetConnectionString(std::string& connection) override;
  PVR_ERROR GetBackendHostname(std::string& hostname) override;

  PVR_ERROR GetCapabilities(kodi::addon::PVRCapabilities& capabilities) override;
  PVR_ERROR GetDriveSpace(uint64_t& total, uint64_t& used) override;

  PVR_ERROR CallEPGMenuHook(const kodi::addon::PVRMenuhook& menuhook,
                            const kodi::addon::PVREPGTag& item) override;
  PVR_ERROR CallChannelMenuHook(const kodi::addon::PVRMenuhook& menuhook,
                                const kodi::addon::PVRChannel& item) override;
  PVR_ERROR CallTimerMenuHook(const kodi::addon::PVRMenuhook& menuhook,
                              const kodi::addon::PVRTimer& item) override;
  PVR_ERROR CallRecordingMenuHook(const kodi::addon::PVRMenuhook& menuhook,
                                  const kodi::addon::PVRRecording& item) override;
  PVR_ERROR CallSettingsMenuHook(const kodi::addon::PVRMenuhook& menuhook) override;

  PVR_ERROR GetEPGForChannel(int channelUid,
                             time_t start,
                             time_t end,
                             kodi::addon::PVREPGTagsResultSet& results) override;
  PVR_ERROR IsEPGTagPlayable(const kodi::addon::PVREPGTag& tag, bool& bIsPlayable) override;
  PVR_ERROR GetEPGTagStreamProperties(
      const kodi::addon::PVREPGTag& tag,
      std::vector<kodi::addon::PVRStreamProperty>& properties) override;
  PVR_ERROR GetProvidersAmount(int& amount) override;
  PVR_ERROR GetProviders(kodi::addon::PVRProvidersResultSet& results) override;
  PVR_ERROR GetChannelGroupsAmount(int& amount) override;
  PVR_ERROR GetChannelGroups(bool bRadio, kodi::addon::PVRChannelGroupsResultSet& results) override;
  PVR_ERROR GetChannelGroupMembers(const kodi::addon::PVRChannelGroup& group,
                                   kodi::addon::PVRChannelGroupMembersResultSet& results) override;
  PVR_ERROR GetChannelsAmount(int& amount) override;
  PVR_ERROR GetChannels(bool bRadio, kodi::addon::PVRChannelsResultSet& results) override;
  PVR_ERROR GetRecordingsAmount(bool deleted, int& amount) override;
  PVR_ERROR GetRecordings(bool deleted, kodi::addon::PVRRecordingsResultSet& results) override;
  PVR_ERROR GetTimerTypes(std::vector<kodi::addon::PVRTimerType>& types) override;
  PVR_ERROR GetTimersAmount(int& amount) override;
  PVR_ERROR GetTimers(kodi::addon::PVRTimersResultSet& results) override;
  PVR_ERROR GetSignalStatus(int channelUid, kodi::addon::PVRSignalStatus& signalStatus) override;
  PVR_ERROR GetChannelStreamProperties(
      const kodi::addon::PVRChannel& channel,
      std::vector<kodi::addon::PVRStreamProperty>& properties) override;
  PVR_ERROR GetRecordingStreamProperties(
      const kodi::addon::PVRRecording& recording,
      std::vector<kodi::addon::PVRStreamProperty>& properties) override;

  ADDON_STATUS SetSetting(const std::string& settingName,
                        const std::string& settingValue);

protected:
  std::string GetRecordingURL(const kodi::addon::PVRRecording& recording);
  bool GetChannel(const kodi::addon::PVRChannel& channel, MagentaChannel& myChannel);

private:
  PVR_ERROR CallMenuHook(const kodi::addon::PVRMenuhook& menuhook);

  void SetStreamProperties(std::vector<kodi::addon::PVRStreamProperty>& properties,
                           const std::string& url,
                           bool realtime, bool playTimeshiftBuffer);

  std::vector<MagentaChannel> m_channels;
  std::vector<MagentaCategory> m_categories;

/*
  std::string m_drmid;
  std::string m_sessionid;
  std::string m_ipaddress;
  std::string m_token;
  std::string m_deviceid;
*/
  HttpClient *m_httpClient;
  CSettings* m_settings;

  bool is_better_resolution(const int alternative, const int current);
  bool MagentaGuestLogin();
  bool MagentaDTAuthenticate();
  bool MagentaAuthenticate();
  bool LoadChannels();

  std::string m_licence_url;
  std::string m_ca_device_id;
  std::string m_epg_https_url;
  std::string m_sam_service_url;
  std::string m_cnonce;
/*
  bool HrtiLogin();
  bool GetIpAddress();
  bool GrantAccess();
  bool RegisterDevice();
  bool LoadChannels();
  bool AuthorizeSession(std::string ref_id, std::string drm_id);
  std::string GetLicense(std::string drm_id, std::string user_id);
*/
//  std::string m_csrfToken;
//  std::string ltrim(const std::string &s);
//  std::string rtrim(const std::string &s);
//  std::string trim(const std::string &s);
};
