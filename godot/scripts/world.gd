extends Node3D

const PlayerScript = preload("res://scripts/player.gd")
var player: FamilyPlayer
var camera: Camera3D
var hud: CanvasLayer
var cash := 250
var reputation := 50
var orders := 0
var chosen_character := ""
var selected_action := ""
var action_position := Vector3.ZERO
var status_label: Label
var stats_label: Label
var selection_panel: PanelContainer
var touch_origin := Vector2.ZERO
var touch_active := false
var touch_mode := false

func _ready() -> void:
    _build_environment()
    _build_hud()
    _show_character_selection()

func _make_box(parent: Node3D, size: Vector3, pos: Vector3, color: Color, collision := true) -> StaticBody3D:
    var root := StaticBody3D.new()
    root.position = pos
    parent.add_child(root)
    var mesh := MeshInstance3D.new()
    var geometry := BoxMesh.new()
    geometry.size = size
    mesh.mesh = geometry
    var mat := StandardMaterial3D.new()
    mat.albedo_color = color
    mesh.material_override = mat
    root.add_child(mesh)
    if collision:
        var collider := CollisionShape3D.new()
        var shape := BoxShape3D.new()
        shape.size = size
        collider.shape = shape
        root.add_child(collider)
    return root

func _build_environment() -> void:
    var sky := WorldEnvironment.new()
    var environment := Environment.new()
    environment.background_mode = Environment.BG_COLOR
    environment.background_color = Color("#86c8f5")
    environment.ambient_light_source = Environment.AMBIENT_SOURCE_COLOR
    environment.ambient_light_color = Color("#e5e6ff")
    environment.ambient_light_energy = 0.8
    sky.environment = environment
    add_child(sky)
    var sunlight := DirectionalLight3D.new()
    sunlight.rotation_degrees = Vector3(-55, -30, 0)
    sunlight.light_energy = 1.5
    sunlight.shadow_enabled = true
    add_child(sunlight)
    _make_box(self, Vector3(100, 0.2, 100), Vector3(0, -0.1, 0), Color("#74ba70"))
    _make_box(self, Vector3(100, 0.03, 6), Vector3(0, 0.01, 0), Color("#666d7b"), false)
    _make_box(self, Vector3(6, 0.03, 100), Vector3(0, 0.02, 0), Color("#666d7b"), false)
    _make_building(Vector3(-12, 0, -13), Vector3(12, 4, 9), Color("#d9b4e9"), "Laundry")
    _make_building(Vector3(12, 0, -13), Vector3(9, 4, 9), Color("#f5d0a3"), "Home")
    _make_box(self, Vector3(3.8, 1.4, 2.2), Vector3(-8, 0.8, 9), Color("#733fae"))
    _make_box(self, Vector3(2, 0.7, 2.3), Vector3(-8, 1.8, 9), Color("#9dd9f4"))
    for i in range(5):
        _make_tree(Vector3(-25 + i * 11, 0, 22))
    _make_action("Wash laundry", Vector3(-12, 0.25, -7), Color("#a6f54e"))
    _make_action("Pickup order", Vector3(-8, 0.25, 6), Color("#ffcb60"))
    _make_action("Rest at home", Vector3(12, 0.25, -7), Color("#79d9ff"))
    _make_action("Family time", Vector3(7, 0.25, -4), Color("#ff9fc8"))

func _make_building(pos: Vector3, size: Vector3, wall: Color, kind: String) -> void:
    _make_box(self, size, pos + Vector3(0, size.y / 2.0, 0), wall)
    _make_box(self, Vector3(size.x + 0.6, 0.5, size.z + 0.6), pos + Vector3(0, size.y + 0.25, 0), Color("#62358e"))
    _make_box(self, Vector3(1.7, 2.4, 0.14), pos + Vector3(0, 1.2, size.z / 2.0 + 0.1), Color("#855b44"), false)
    for x in [-size.x * 0.28, size.x * 0.28]:
        _make_box(self, Vector3(1.5, 1.2, 0.15), pos + Vector3(x, 2.6, size.z / 2.0 + 0.12), Color("#8ed2ed"), false)

func _make_tree(pos: Vector3) -> void:
    _make_box(self, Vector3(0.4, 2.5, 0.4), pos + Vector3(0, 1.25, 0), Color("#956a49"))
    var leaves := MeshInstance3D.new()
    var sphere := SphereMesh.new()
    sphere.radius = 1.6
    sphere.height = 3.2
    leaves.mesh = sphere
    var mat := StandardMaterial3D.new()
    mat.albedo_color = Color("#3da65a")
    leaves.material_override = mat
    leaves.position = pos + Vector3(0, 3.2, 0)
    add_child(leaves)

func _make_action(title: String, pos: Vector3, color: Color) -> void:
    var area := Area3D.new()
    area.position = pos
    area.set_meta("action", title)
    add_child(area)
    var marker := MeshInstance3D.new()
    var cylinder := CylinderMesh.new()
    cylinder.top_radius = 0.8
    cylinder.bottom_radius = 0.8
    cylinder.height = 0.08
    marker.mesh = cylinder
    var mat := StandardMaterial3D.new()
    mat.albedo_color = color
    mat.emission_enabled = true
    mat.emission = color
    mat.emission_energy_multiplier = 0.4
    marker.material_override = mat
    area.add_child(marker)
    var collision := CollisionShape3D.new()
    var shape := CylinderShape3D.new()
    shape.radius = 0.9
    shape.height = 0.4
    collision.shape = shape
    area.add_child(collision)

func _build_hud() -> void:
    hud = CanvasLayer.new()
    add_child(hud)
    var overlay := Control.new()
    overlay.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
    overlay.mouse_filter = Control.MOUSE_FILTER_IGNORE
    hud.add_child(overlay)
    stats_label = Label.new()
    stats_label.position = Vector2(20, 16)
    stats_label.add_theme_font_size_override("font_size", 21)
    overlay.add_child(stats_label)
    status_label = Label.new()
    status_label.position = Vector2(20, 58)
    status_label.add_theme_font_size_override("font_size", 17)
    status_label.text = "Choose a character to start."
    overlay.add_child(status_label)
    _update_stats()

func _show_character_selection() -> void:
    selection_panel = PanelContainer.new()
    selection_panel.set_anchors_and_offsets_preset(Control.PRESET_CENTER)
    selection_panel.custom_minimum_size = Vector2(360, 290)
    hud.add_child(selection_panel)
    var content := VBoxContainer.new()
    selection_panel.add_child(content)
    var heading := Label.new()
    heading.text = "THE FIRST FAMILY\nChoose your character"
    heading.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
    content.add_child(heading)
    for character_name in ["Jay", "Esined", "Jahdē"]:
        var button := Button.new()
        button.text = character_name
        button.custom_minimum_size.y = 54
        button.pressed.connect(_choose_character.bind(character_name))
        content.add_child(button)

func _choose_character(character_name: String) -> void:
    chosen_character = character_name
    selection_panel.queue_free()
    player = PlayerScript.new()
    player.character_name = character_name
    player.position = Vector3(0, 1.1, 9)
    add_child(player)
    camera = player.camera_pivot.get_child(0) as Camera3D
    status_label.text = "Playing as %s. Tap ground to walk; tap glowing circles to act." % character_name
    _update_stats()

func _unhandled_input(event: InputEvent) -> void:
    if player == null or camera == null:
        return
    if event is InputEventScreenTouch and event.pressed:
        _point_to(event.position)
    elif event is InputEventMouseButton and event.pressed and event.button_index == MOUSE_BUTTON_LEFT:
        _point_to(event.position)

func _point_to(screen_position: Vector2) -> void:
    var origin := camera.project_ray_origin(screen_position)
    var direction := camera.project_ray_normal(screen_position)
    var query := PhysicsRayQueryParameters3D.create(origin, origin + direction * 100)
    query.collide_with_areas = true
    var result := get_world_3d().direct_space_state.intersect_ray(query)
    if result.is_empty():
        return
    var collider: Object = result["collider"]
    if collider is Area3D and collider.has_meta("action"):
        selected_action = str(collider.get_meta("action"))
        action_position = collider.global_position
        player.move_to(action_position)
        status_label.text = "Walking to %s..." % selected_action
    else:
        selected_action = ""
        player.move_to(result["position"])

func _process(_delta: float) -> void:
    if player == null or selected_action.is_empty():
        return
    if player.global_position.distance_to(action_position) < 1.3:
        _complete_action(selected_action)
        selected_action = ""

func _complete_action(action: String) -> void:
    var outcome := randf()
    if action == "Wash laundry":
        if outcome < 0.22:
            cash -= 12
            reputation -= 3
            status_label.text = "A washer broke down! Repairs cost $12."
        else:
            cash += 38
            orders += 1
            reputation += 2
            status_label.text = "Laundry complete! Earned $38."
        player.energy = maxf(0, player.energy - 15)
    elif action == "Pickup order":
        if outcome < 0.28:
            cash -= 6
            reputation -= 4
            status_label.text = "Late delivery! Fuel cost $6; reputation dropped."
        else:
            cash += 45
            orders += 1
            reputation += 3
            status_label.text = "Delivery complete! Earned $45."
        player.energy = maxf(0, player.energy - 18)
    elif action == "Rest at home":
        player.energy = minf(100, player.energy + 35)
        status_label.text = "Rested and recovered 35 energy."
    else:
        reputation += 1
        status_label.text = "Quality family time. Relationships improved."
    _update_stats()

func _update_stats() -> void:
    stats_label.text = "Empire Cash: $%d  |  Reputation: %d  |  Orders: %d" % [cash, reputation, orders]
