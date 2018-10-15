from abc import ABC, abstractmethod

import bpy

class Scene_types():
    #abstracte Klasse fuer Scenen Typen
    state_manager=None
    def __init__(self,state_manager):
        self.state_manager=state_manager

    def register(self,dict,enum):
        #registriert das Module in der jeweiligen Liste
        pass
    

    def unregister(self,dict,enum):
        pass
    def draw(self,context):
        pass

    def fill_states(self,cls):
        pass
    def remove_states(self,cls):
        pass

class State_manager:
    #manget die KLassen der Scene_tpyes und ihre Ablaeufe

    JPCWorldStart=[[]]
    JPCAnimationStart=[[]]
    JPCFrameStart=[[]]
    JPCFrameEnd=[[]]
    JPCAnimationEnd=[[]]
    JPCWorldEnd=[[]]



    
    _id_status=0

    #ueberpruft ob die Klasse bereit zum rendern ist
    ready=False

    Statuslist=["WORLDSTART","ANIMATIONSTART","FRAMESTART","RENDER","FRAMEEND","ANIMATIONEND","WORLDEND"]

    def render_setup(self,scene):
        self.scene=scene
        self.ready=True
    

    def _set_Status(self,Value):
        ''' WORLDBEGINN->ANIMATIONSTART->FRAMESTART->RENDER->FRAMEEND->ANIMATIONEND->WORLDEND
            0                1              2           3       4           5           6
        '''
        print("Status wird auf :",Value," gesetzt")
        if (not self.ready):
            raise Exception("render_setup muss erst ausgeführt werden")

        if Value in self.Statuslist:
            cvalue_idx=self.Statuslist.index(Value)
            #Worldend->Worldbeginn
            Worldstart=cvalue_idx==0 and self._id_status==6
            
            #Animationend->Animationstart | Worldbeginn-> Animationstart
            Animationstart=cvalue_idx==1 and (self._id_status==5 or self._id_status==0)
            
            #Animationstart->Framebeginn | Frameend->Framebeginn
            Framestart=cvalue_idx==2 and (self._id_status==1 or self._id_status==4)
            
            #Framebeginn->Render
            Render=cvalue_idx==3 and self._id_status==2
            
            #Render->Frameend
            Frameend=cvalue_idx==4 and self._id_status==3

            #Frameend->Animationend 
            Animationend=cvalue_idx==5 and self._id_status==4

            #Animationend->Worldend
            Worldend=cvalue_idx==6 and self._id_status==5


            if (Worldstart or Animationstart or Framestart or Render or Frameend or Animationend or Worldend):
                #WORLDEND->WORLDBEGINN
                self._id_status=Value

                self.update_status(self.scene)
            elif (self.Statuslist[cvalue_idx]==Value):
                pass
            else:
                raise Exception("neuer Status {v} kann nicht auf {x} folgen".format(v=Value,x=self.Statuslist[self._id_status]))
            
        else:
            raise Exception("Status: {Value} ist kein Wert von {Statusliste}".format())
    
    
    def _get_Status(self):
        return self.Statuslist[self._id_status]
    Status=property(_get_Status,_set_Status)
    def update_status(self,scene):
        
        if self._id_status==0:
            self.update_list(self.JPCWorldStart,scene)
        elif self._id_status==1:
            self.update_list(self.JPCAnimationStart,scene)
        elif self._id_status==2:
            self.update_list(self.JPCFrameStart,scene)
        #elif self._id_status==3:
        #render sollte nichts ge�ndert werden
        elif self._id_status==4:
            self.update_list(self.JPCFrameEnd,scene)
        elif self._id_status==5:
            self.update_list(self.JPCAnimationEnd,scene)
        elif self._id_status==6:
            self.update_list(self.JPCWorldEnd,scene)
    

    def update_list(update_array,scene):
        for func_arr in update_array:
            func_arr[0](*func_arr[1],)

def register(engine):
    
    #Materials=[]
    #Images=[]
    #Shapes=[]
    #Lights=[]
    #Cameras=[]
    #Sampler=[]
    #listen muessen regestriert werden
    #Materialen
    bpy.types.Material.JPCvariations=[]
    emun=[]


    bpy.types.Camera.JPCvariations=[]
    bpy.types.Object.JPCvariations=[]
    bpy.types.Lamp.JPCvariations=[]


import importlib.util
import os

def JPC_get_attr(self,name):
    cls=self.JPCvariations[self["JPCvariation"]]
    return getattr(cls,name)

def _set_variation(self,Value):
    #der Wert davor
    if len(self.JPCvariations)==0:
        return None
    if "JPCvariation" in self:
        preval=self["JPCvariation"]
        self.JPCvariations[preval].remove_states(self)
    self.JPCvariations[Value].fill_states(self)
    self["JPCvariation"]=Value


def register_a_type(type,path,statemanager):
    type.JPCvariations=[]
    type.JPC_get_attr=JPC_get_attr
    enum=[]
    files=os.listdir(path)
    for file in files:
        if file[-3:]==".py":
            spec = importlib.util.spec_from_file_location(file[:-2], path+"\\"+file)
            foo = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(foo)
            foo.register(type.JPCvariations,enum,statemanager)
    type.JPCvariation=bpy.props.EnumProperty(items=enum,set=_set_variation)
