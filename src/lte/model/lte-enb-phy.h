/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 * Author: Marco Miozzo <marco.miozzo@cttc.es>
 */

#ifndef ENB_LTE_PHY_H
#define ENB_LTE_PHY_H


#include "lte-phy.h"
#include <ns3/lte-enb-phy-sap.h>
#include <map>
#include <ns3/lte-ue-phy.h>

namespace ns3 {

class PacketBurst;
class LteNetDevice;

/**
 * LteEnbPhy models the physical layer for the eNodeB
 */
class LteEnbPhy : public LtePhy
{

  friend class EnbMemberLteEnbPhySapProvider;

public:
  LteEnbPhy ();

  /**
   * \brief Create the eNB phy layer
   * \param d the device where the phy layer is attached
   */
  LteEnbPhy (Ptr<LteNetDevice> d);
  virtual ~LteEnbPhy ();

  static TypeId GetTypeId (void);


  /**
  * \brief Get the PHY SAP provider
  * \return a pointer to the SAP Provider of the PHY
  */
  LteEnbPhySapProvider* GetLteEnbPhySapProvider ();

  /**
  * \brief Set the PHY SAP User
  * \param s a pointer to the PHY SAP user
  */
  void SetLteEnbPhySapUser (LteEnbPhySapUser* s);


  /**
  * \brief Queue the MAC PDU to be sent
  * \param p the MAC PDU to sent
  */
  virtual void DoSendMacPdu (Ptr<Packet> p);


  void DoSetDownlinkSubChannels ();

  /**
   * \brief Create the PSD for TX
   */
  virtual Ptr<SpectrumValue> CreateTxPowerSpectralDensity ();

  /**
   * \brief Calculate the channel quality for a given UE
   * \param sinr a list of computed SINR
   * \param ue the UE
   */
  void CalcChannelQualityForUe (std::vector <double> sinr, Ptr<LteSpectrumPhy> ue);

  /**
   * \brief Send the control message
   * \param msg the message to send
   */
  // virtual void SendIdealControlMessage (Ptr<IdealControlMessage> msg);  // legacy
  /**
   * \brief Receive the control message
   * \param msg the received message
   */
  virtual void ReceiveIdealControlMessage (Ptr<IdealControlMessage> msg);


  void DoSendIdealControlMessage (Ptr<IdealControlMessage> msg);

  bool AddUePhy (uint8_t rnti, Ptr<LteUePhy> phy);

  bool DeleteUePhy (uint8_t rnti);


  /**
   * \brief Start a LTE frame
   */
  void StartFrame (void);
  /**
   * \brief Start a LTE sub frame
   */
  void StartSubFrame (void);
  /**
   * \brief End a LTE sub frame
   */
  void EndSubFrame (void);
  /**
   * \brief End a LTE frame
   */
  void EndFrame (void);

  /**
   * \brief PhySpectrum received a new PHY-PDU
   */
  void PhyPduReceived (Ptr<Packet> p);
  
  // inherited from LtePhy
  virtual void GenerateCqiFeedback (const SpectrumValue& sinr);
  

private:
  std::map <uint8_t, Ptr<LteUePhy> > m_ueAttached;

  LteEnbPhySapProvider* m_enbPhySapProvider;
  LteEnbPhySapUser* m_enbPhySapUser;

  uint32_t m_nrFrames;
  uint32_t m_nrSubFrames;
};


}

#endif /* LTE_ENB_PHY_H */