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
            AddCommand("ViewConnectionInfo", "", "View connection details for a user.",
                        [=](const CString& sLine) { ViewConnectionInfo(sLine); });
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
                    if (pNetwork->IsIRCConnected()) {
                        PutModNotice("LAUN " + it.first + " " + pNetwork->GetName() + " Yes " +
                                    pNetwork->GetBindHost() + " " +pNetwork->GetIRCServer() + 
                                    pNetwork->GetIRCNick().GetNickMask());
                    } else {
                        PutModNotice("LAUN " + it.first + " " + pNetwork->GetName() + " No " +
                                    pNetwork->GetBindHost());
                    } 
                }
            }            
        }

        void ViewConnectionInfo(const CString& sLine) {
            if (!GetUser()->IsAdmin()) {
                PutModule("Access denied!");
                return;
            }

            const CString sUsername = sLine.Token(1);

            if (sUsername.empty()) {
                PutModNotice("Usage: ViewConnectionInfo <username>");
                return;
            }

            CUser* pUser = CZNC::Get().FindUser(sUsername);
            if (!pUser) {
                PutModNotice("Error: User [" + sUsername + "] does not exist!");
                return;
            }

            const vector<CIRCNetwork*>& vNetworks = pUser->GetNetworks();
            for (const CIRCNetwork* pNetwork : vNetworks) {
                if (pNetwork->IsIRCConnected()) {
                    PutModNotice("VCI " + sUsername + " " + pNetwork->GetName() + " Yes " +
                                pNetwork->GetBindHost() + " " +pNetwork->GetIRCServer() + 
                                pNetwork->GetIRCNick().GetNickMask());
                } else {
                    PutModNotice("VCI " + sUsername + " " + pNetwork->GetName() + " No " +
                                pNetwork->GetBindHost());
                }
            }
        }
};


GLOBALMODULEDEFS(CPanicBNCMod, "PanicBNC Assistance Module")