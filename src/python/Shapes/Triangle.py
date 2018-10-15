from JPCEngine import Scene_types


import bpy

class Triangle(Scene_types.Scene_types):
    def __init__(self,state_manager):
        Scene_types.Scene_types.__init__(self, state_manager)
     
    
    
    def register(self,dict,enum):
        enum.append(("Triangle","Triangle","Ein Mesh aus Dreicken",len(dict)))
        dict.append(self)

    def unregister(self,dict,enum):
        del dict["Triangle"]
        for item in enum:
            if item[1]=="Triangle":
                break
        enum.remove(item)

    def draw(self,context):
        pass

    def fill_states(self,cls):
        print("test")

    def remove_states(self,cls):
        pass



def register(dict,enum,state_manager):
    T=Triangle(state_manager)
    T.register(dict,enum)
def unregister(dict,enum):
    T=dict["Triangle"]
    T.unregister(dict,enum)
