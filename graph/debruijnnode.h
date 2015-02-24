//Copyright 2015 Ryan Wick

//This file is part of Bandage

//Bandage is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Bandage is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Bandage.  If not, see <http://www.gnu.org/licenses/>.


#ifndef DEBRUIJNNODE_H
#define DEBRUIJNNODE_H

#include <QByteArray>
#include <vector>
#include <ogdf/basic/Graph.h>
#include "../program/globals.h"
#include <QColor>

class OgdfNode;
class DeBruijnEdge;
class GraphicsItemNode;
class BlastResult;

class DeBruijnNode
{
public:
    DeBruijnNode(int number, int length, double coverage, QByteArray sequence);
    ~DeBruijnNode();

    int m_number;
    int m_length;
    double m_coverage;
    double m_coverageRelativeToMeanDrawnCoverage;
    QByteArray m_sequence;
    ContiguityStatus m_contiguityStatus;
    DeBruijnNode * m_reverseComplement;
    OgdfNode * m_ogdfNode;
    GraphicsItemNode * m_graphicsItemNode;
    std::vector<DeBruijnEdge *> m_edges;
    bool m_startingNode;
    bool m_drawn;
    int m_highestDistanceInNeighbourSearch;
    QColor m_customColour;
    QString m_customLabel;
    BlastResult * m_blastResult;

    void addEdge(DeBruijnEdge * edge);
    void resetNode();
    bool hasGraphicsItem() {return m_graphicsItemNode != 0;}
    bool inOgdf() {return m_ogdfNode != 0;}
    bool notInOgdf() {return !inOgdf();}
    bool thisOrReverseComplementInOgdf() {return (inOgdf() || m_reverseComplement->inOgdf());}
    bool thisOrReverseComplementNotInOgdf() {return !thisOrReverseComplementInOgdf();}
    void addToOgdfGraph(ogdf::Graph * ogdfGraph);
    void determineContiguity(DeBruijnNode * previousNode);
    void setContiguityStatus(ContiguityStatus newStatus);
    bool isOnlyPathInItsDirection(DeBruijnNode * connectedNode,
                                  std::vector<DeBruijnNode *> * incomingNodes,
                                  std::vector<DeBruijnNode *> * outgoingNodes);
    bool isNotOnlyPathInItsDirection(DeBruijnNode * connectedNode,
                                     std::vector<DeBruijnNode *> * incomingNodes,
                                     std::vector<DeBruijnNode *> * outgoingNodes)
    {return !isOnlyPathInItsDirection(connectedNode, incomingNodes, outgoingNodes);}
    QByteArray getFasta();
    void labelNeighbouringNodesAsDrawn(int nodeDistance, DeBruijnNode * callingNode);
};

#endif // DEBRUIJNNODE_H
