
class GameState:
    def __init__(self):
        self.curr_local = "Hollow Wood" 
        self.locations = ["Hollow Wood", "Farecast", "Ommnicent"]
        self.intro_complete = False
        pass

class Player:
    def __init__(self, player_class, player_name):
        self.name = player_name
        self.class_name = player_class["Class"]

        self.hp = player_class['hp']
        self.max_hp = player_class['hp']

        self.strength = player_class['Strength']
        self.max_strength = player_class['Strength']

        self.speed = player_class['Speed']
        self.max_speed = player_class['Speed']

        self.mana = player_class['Mana']
        self.max_mana = player_class['Mana']

        self.level = 1
        self.gold = 0
        self.weapon = None
        self.inventory = {}
    pass