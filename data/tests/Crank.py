#import rpdb2
#rpdb2.start_embedded_debugger("test")
import LabRPS
import Part
import Draft
from LabRPS import Base

circ1= Part.makeCircle(
	5,
	LabRPS.Vector(10,18,10), LabRPS.Vector(1,0,0))

circ2 = Part.makeCircle(5)

def DrawMyPart(points, extrude):
	obj1 = Draft.makeWire(points,closed=True,face=True,support=None)
	face1 = Part.Face(obj1.Shape)
	body1= face1.extrude(extrude)
	Part.show(body1)

# part1
DrawMyPart([
	LabRPS.Vector(0,0,0),
	LabRPS.Vector(45,0,0),
	LabRPS.Vector(45,20,0),
	LabRPS.Vector(0,20,0),
	], Base.Vector(0,0,4))
DrawMyPart([
	LabRPS.Vector(0,20,0),
	LabRPS.Vector(0,180,0),
	LabRPS.Vector(25,180,0),
	LabRPS.Vector(25,20,0),
	], Base.Vector(0,0,4))
DrawMyPart([
	LabRPS.Vector(0,180,0),
	LabRPS.Vector(0,200,0),
	LabRPS.Vector(45,200,0),
	LabRPS.Vector(45,180,0),
	], Base.Vector(0,0,4))

DrawMyPart([
	LabRPS.Vector(25,20,0),
	LabRPS.Vector(25,180,0),
 	LabRPS.Vector(25,180,9.2),
 	LabRPS.Vector(25,20,9.2),
	], Base.Vector(0,0,4))


# part2
points=[
	LabRPS.Vector(45,200,0),
	LabRPS.Vector(68,200,25),
	LabRPS.Vector(68,0,25),
	LabRPS.Vector(45,0,0),
	LabRPS.Vector(45,200,0),
]
DrawMyPart([
	LabRPS.Vector(45,200,0),
	LabRPS.Vector(68,200,25),
	LabRPS.Vector(68,180,25),
	LabRPS.Vector(45,180,0),
	], Base.Vector(0,0,4))
DrawMyPart([
	LabRPS.Vector(68,180,25),
	LabRPS.Vector(56.7,180,13),
	LabRPS.Vector(56.7,20,13),
	LabRPS.Vector(68,20,25),
	], Base.Vector(0,0,4))
DrawMyPart([
	LabRPS.Vector(45,0,0),
	LabRPS.Vector(68,0,25),
	LabRPS.Vector(68,20,25),
	LabRPS.Vector(45,20,0),
	], Base.Vector(0,0,4))

DrawMyPart([
 	LabRPS.Vector(25,20,0),
 	LabRPS.Vector(45,20,0),
 	LabRPS.Vector(45,20,9.2),
 	LabRPS.Vector(25,20,9.2),
 	], Base.Vector(0,0,4))
DrawMyPart([
 	LabRPS.Vector(25,180,0),
 	LabRPS.Vector(45,180,0),
 	LabRPS.Vector(45,180,9.2),
 	LabRPS.Vector(25,180,9.2),
 	], Base.Vector(0,0,4))


# part3
DrawMyPart([
	LabRPS.Vector(68,200,25),
	LabRPS.Vector(68,200,35),
	LabRPS.Vector(68,0,35),
	LabRPS.Vector(68,0,25),
	LabRPS.Vector(68,200,25),
	], Base.Vector(0,0,4))


circ1= Draft.makeCircle(
	5,
	Base.Placement(10,18,10),
	LabRPS.Vector(1,0,0))

circ2 = Draft.makeCircle(5)