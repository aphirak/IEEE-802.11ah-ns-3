/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Budiarto Herman
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
 * Author: Budiarto Herman <budiarto.herman@magister.fi>
 *
 */

#ifndef LTE_TEST_CELL_SELECTION_H
#define LTE_TEST_CELL_SELECTION_H

#include <ns3/test.h>
#include <ns3/nstime.h>
#include <ns3/node-container.h>
#include <ns3/vector.h>
#include <ns3/lte-ue-rrc.h>
#include <vector>

namespace ns3 {


/**
 * \brief Test suite for executing the cell selection test cases in without-EPC
 *        and with-EPC scenarios.
 *
 * \sa ns3::LteCellSelectionTestCase
 */
class LteCellSelectionTestSuite : public TestSuite
{
public:
  LteCellSelectionTestSuite ();
};



class LteUeNetDevice;

/**
 * \brief Testing the initial cell selection procedure by UE at IDLE state in
 *        the beginning of simulation.
 */
class LteCellSelectionTestCase : public TestCase
{
public:
  /**
   * \brief A set of input parameters for setting up a UE in the simulation.
   */
  struct UeSetup_t
  {
    Vector position; ///< The position, relative to the inter site distance, where the UE will be spawned in the simulation.
    bool isCsgMember; ///< Whether UE is allowed access to CSG cell.
    Time checkPoint; ///< The time in simulation when the UE is verified by the test script.
    uint16_t expectedCellId1; ///< The cell ID that the UE is expected to attach to (0 means that the UE should not attach to any cell).
    uint16_t expectedCellId2; ///< An alternative cell ID that the UE is expected to attach to (0 means that this no alternative cell is expected).
    UeSetup_t (double relPosX, double relPosY, bool isCsgMember, Time checkPoint,
               uint16_t expectedCellId1, uint16_t expectedCellId2);
  };

  /**
   * \brief Creates an instance of the initial cell selection test case.
   * \param name name of this test
   * \param isEpcMode set to true for setting up simulation with EPC enabled
   * \param isIdealRrc if true, simulation uses Ideal RRC protocol, otherwise
   *                   simulation uses Real RRC protocol
   * \param interSiteDistance the distance between eNodeB in meters
   * \param ueSetupList a list of UE configuration to be installed in the
   *                    simulation
   * \param rngRun the number of run to be used by the random number generator
   */
  LteCellSelectionTestCase (std::string name, bool isEpcMode, bool isIdealRrc,
                            double interSiteDistance,
                            std::vector<UeSetup_t> ueSetupList,
                            int64_t rngRun);

  virtual ~LteCellSelectionTestCase ();

private:
  /**
   * \brief Setup the simulation according to the configuration set by the
   *        class constructor, run it, and verify the result.
   */
  virtual void DoRun ();

  /**
   * \brief Verifies if the given UE is attached to either of the given two
   *        cells and in a CONNECTED_NORMALLY state.
   */
  void CheckPoint (Ptr<LteUeNetDevice> ueDev, uint16_t expectedCellId1,
                   uint16_t expectedCellId2);

  void StateTransitionCallback (std::string context, uint64_t imsi,
                                uint16_t cellId, uint16_t rnti,
                                LteUeRrc::State oldState, LteUeRrc::State newState);
  void InitialCellSelectionEndOkCallback (std::string context, uint64_t imsi,
                                          uint16_t cellId);
  void InitialCellSelectionEndErrorCallback (std::string context, uint64_t imsi,
                                             uint16_t cellId);
  void ConnectionEstablishedCallback (std::string context, uint64_t imsi,
                                      uint16_t cellId, uint16_t rnti);

  bool m_isEpcMode;
  bool m_isIdealRrc;
  double m_interSiteDistance;
  std::vector<UeSetup_t> m_ueSetupList;
  int64_t m_rngRun;

  /// The current UE RRC state.
  std::vector<LteUeRrc::State> m_lastState;

}; // end of class LteCellSelectionTestCase



} // end of namespace ns3


#endif /* LTE_TEST_CELL_SELECTION_H */
