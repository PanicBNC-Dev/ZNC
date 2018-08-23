/*
 * Copyright (C) 2004-2018 PanicBNC, see the NOTICE file for details.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <znc/Modules.h>
#include <znc/IRCNetwork.h>
#include <znc/User.h>

using std::map;
using std::vector;

class CPanicBNCMod : public CModule {
    public:
        MODCONSTRUCTOR(CPanicBNCMod) {
            AddHelpCommand();
            AddCommand("ListAllUserNetworks", "", "Lists all user networks.",
                        [=](const CString& sLine) { ListAllUserNetworks(sLine); });
            AddCommand("ListAllQueuedNetworks", "", "Counts and returns all queued connections.",
                        [=](const CString& sLine) { ListAllQueuedNetworks(sLine); });
        }

        void ListAllUserNetworks(const CString& sLine) {
            if (!GetUser()->IsAdmin()) {
                PutModule("Access denied!");
                return;
            }
            const map<CString, CUser*>& msUsers = CZNC::Get().GetUserMap();
            for (const auto& it : msUsers) {
                const vector<CIRCNetwork*>& vNetworks = it.second->GetNetworks();
                for (const CIRCNetwork* pNetwork : vNetworks) {
                    PutModNotice("LAUN " + it.first + " " + pNetwork->GetName() + " " +  CString(pNetwork->IsIRCConnected()) + " "
                    + pNetwork->GetIRCServer() + " " + pNetwork->GetIRCNick().GetNickMask() + " " + pNetwork->GetBindHost()); 
                }
            }            
        }

        void ListAllQueuedNetworks(const CString& sLine) {
            if (!GetUser()->IsAdmin()) {
                PutModule("Access denied!");
                return
            }

            const map<CString, CUser*>& msUsers = CZNC::Get().GetUserMap();
            for (const auto& it : msUsers) {
                const vector<CIRCNetwork*>& vNetworks = it.second->GetNetworks();
                for (const CIRCNetwork* pNetwork : vNetworks) {
                    CIRCSock* pIRCSock = pNetwork->GetIRCSock();
                    if (pIRCSock && !pIRCSock->IsConnected()) {
                        PutModNotice("LAQN " + it.first + "/" + pNetwork->GetName());
                    }
                }
            }
        }
};


GLOBALMODULEDEFS(CPanicBNCMod, "PanicBNC Assistance Module")