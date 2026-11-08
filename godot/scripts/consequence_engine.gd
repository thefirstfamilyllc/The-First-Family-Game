extends RefCounted
class_name ConsequenceEngine

# One shared world simulation. Account permissions govern which actions are
# available; the world and economy are not split into separate editions.
var world_state := {
    "cash": 250,
    "reputation": 50,
    "heat": 0,
    "legal_status": "clear",
    "aviation_skill": 0,
    "licenses": [],
    "history": []
}
var rng := RandomNumberGenerator.new()

func _init() -> void:
    rng.randomize()

func allowed_actions(context: String, adult_account: bool) -> Array[String]:
    match context:
        "store":
            if adult_account:
                return ["Shop", "Talk to clerk", "Apply for work", "Attempt robbery", "Leave"]
            return ["Shop", "Talk to clerk", "Apply for work", "Leave"]
        "airport":
            if adult_account:
                return ["Explore airport", "Take flight lesson", "Rent aircraft", "Leave"]
            return ["Explore airport", "Take flight lesson", "Leave"]
        _:
            return ["Explore"]

func resolve(action: String, adult_account: bool) -> Dictionary:
    var permitted := false
    for context in ["store", "airport"]:
        if action in allowed_actions(context, adult_account):
            permitted = true
    if not permitted:
        return {"ok": false, "message": "That action is unavailable for this account."}
    var text := ""
    var roll := rng.randf()
    match action:
        "Shop":
            if int(world_state["cash"]) >= 15:
                world_state["cash"] -= 15
                text = "Purchased supplies for $15."
            else:
                text = "Not enough Empire Cash to purchase supplies."
        "Talk to clerk":
            world_state["reputation"] = mini(100, int(world_state["reputation"]) + 1)
            text = "You had a friendly conversation with the clerk."
        "Apply for work":
            if roll < 0.5:
                world_state["cash"] += 40
                text = "You completed a short shift and earned $40."
            else:
                text = "The store has no shifts available today."
        "Attempt robbery":
            world_state["heat"] += 25
            world_state["reputation"] = maxi(0, int(world_state["reputation"]) - 12)
            if roll < 0.38:
                world_state["cash"] += 85
                text = "You escaped with $85, but witnesses may remember you."
            elif roll < 0.75:
                world_state["legal_status"] = "wanted"
                text = "The attempt failed. Police are looking for you."
            else:
                world_state["legal_status"] = "arrested"
                world_state["cash"] = maxi(0, int(world_state["cash"]) - 75)
                text = "You were arrested and faced $75 in immediate costs."
        "Explore airport":
            text = "You explored the terminal and discovered aviation opportunities."
        "Take flight lesson":
            if int(world_state["cash"]) >= 35:
                world_state["cash"] -= 35
                world_state["aviation_skill"] += 1
                text = "Flight lesson completed. Aviation skill increased."
            else:
                text = "You need $35 Empire Cash for a flight lesson."
        "Rent aircraft":
            if int(world_state["aviation_skill"]) < 2:
                text = "You need more flight training before renting an aircraft."
            elif int(world_state["cash"]) < 100:
                text = "You need $100 Empire Cash to rent an aircraft."
            else:
                world_state["cash"] -= 100
                text = "Aircraft rental approved. Flight controls are a future milestone."
        "Leave":
            text = "You left without taking further action."
    world_state["history"].append({"action": action, "result": text})
    return {"ok": true, "message": text, "state": world_state.duplicate(true)}
