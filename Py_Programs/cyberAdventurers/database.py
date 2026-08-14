import json
from pathlib import Path
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from Object_Classes import Player, Game_State

def class_data(class_name) -> dict:
    class_file_name = "json/classes.json"
    with open(class_file_name, "r") as file:
        data = json.load(file)

    class_data = data[class_name]

    return class_data

def get_player_file():
    
    while(True):
        #display all the files the player created
        if Path('Saves').exists() == False:
            print(" You have no save files, please start a new game")
            print("")
            print(" [ Press any key to continue ]")
            input()
            return False
        
        saved_games = [f for f in Path('Saves').iterdir()]

        print(" Pick a save file")
        print("")
        for index, save in enumerate(saved_games):
            print(f"[ {index} ] {save.name}")

        user_save = input()

        if(user_save > len(saved_games) - 1 or user_save < len(saved_games) - 1 or user_save.isdigit == False):
            print(" Please input a valid file number")
            print("")
            print(" [ Press any key to continue ]")
            input()
            continue
        
        return saved_games[user_save].name

def save_game_state(player_data: Player, game_data: Game_State):
   game_data = {
       "GameState":{
           "Player_Data":{
               "name": player_data.name,
               "class_name": player_data.class_name,
               "hp": player_data.hp,
               "strength": player_data.strength,
               "mana": player_data.mana,
               "speed": player_data.speed 
            },

           "Game_Data":{
               "current_loc": game_data.curr_local,
               "unlocked_locations": game_data.locations, 
            } 
        } 
    }

   file_name = "Saves/" + player_data.name + "save.json"

   with open(file_name, "w") as file:
       json.dump(game_data, file, indent=4)