extends Control
class_name CharacterCreator

signal confirmed(profile: Dictionary)

var profile := {
    "template": "Jay",
    "name": "Jay",
    "skin": 2,
    "hair_style": 0,
    "hair_color": 0,
    "eye_color": 0,
    "face_shape": 1,
    "ear_size": 1,
    "body_build": 1,
    "height": 1.0,
    "outfit": 0
}
const SKIN_COLORS := ["#f4d5bd", "#cf9977", "#956446", "#603e32", "#392721"]
const HAIR_COLORS := ["#211b1a", "#6b3f25", "#b78b55", "#d8d1c7", "#8d49bd", "#4c8aab"]
const EYE_COLORS := ["#5c3824", "#3d765c", "#507ab0", "#888888", "#241e1a"]
const OUTFIT_COLORS := ["#713fa7", "#2e343d", "#89bb4b", "#d94e76", "#e5a43e"]
var preview: SubViewport
var preview_body: MeshInstance3D
var preview_head: MeshInstance3D
var preview_hair: MeshInstance3D
var preview_eyes: Array[MeshInstance3D] = []
var fields: Dictionary = {}

func _ready() -> void:
    set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
    var background := ColorRect.new()
    background.color = Color("#182037")
    background.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
    add_child(background)
    var scroll := ScrollContainer.new()
    scroll.set_anchors_and_offsets_preset(Control.PRESET_FULL_RECT)
    add_child(scroll)
    var layout := HBoxContainer.new()
    layout.size_flags_horizontal = Control.SIZE_EXPAND_FILL
    scroll.add_child(layout)
    var settings := VBoxContainer.new()
    settings.custom_minimum_size = Vector2(340, 0)
    layout.add_child(settings)
    var title := Label.new()
    title.text = "CREATE YOUR CHARACTER"
    title.add_theme_font_size_override("font_size", 25)
    settings.add_child(title)
    var template := OptionButton.new()
    for name in ["Jay", "Esined", "Jahdē"]:
        template.add_item(name)
    template.item_selected.connect(_template_changed)
    _add_field(settings, "Starting character", template)
    var name_edit := LineEdit.new()
    name_edit.text = profile["name"]
    name_edit.max_length = 32
    name_edit.text_changed.connect(func(value: String): profile["name"] = value)
    _add_field(settings, "Character name", name_edit)
    for key in ["skin", "hair_style", "hair_color", "eye_color", "face_shape", "ear_size", "body_build", "outfit"]:
        var picker := OptionButton.new()
        var choices: Array[String] = []
        match key:
            "skin": choices = ["Light", "Tan", "Brown", "Deep brown", "Dark"]
            "hair_style": choices = ["Short", "Curly", "Afro", "Long", "Bald"]
            "hair_color": choices = ["Black", "Brown", "Blonde", "Silver", "Purple", "Blue"]
            "eye_color": choices = ["Brown", "Green", "Blue", "Gray", "Dark"]
            "face_shape": choices = ["Narrow", "Balanced", "Wide"]
            "ear_size": choices = ["Small", "Medium", "Large"]
            "body_build": choices = ["Slim", "Average", "Broad"]
            "outfit": choices = ["Purple", "Charcoal", "Green", "Pink", "Gold"]
        for choice in choices:
            picker.add_item(choice)
        picker.select(int(profile[key]))
        picker.item_selected.connect(_set_choice.bind(key))
        fields[key] = picker
        _add_field(settings, key.replace("_", " ").capitalize(), picker)
    var height_slider := HSlider.new()
    height_slider.min_value = 0.8
    height_slider.max_value = 1.2
    height_slider.step = 0.05
    height_slider.value = 1.0
    height_slider.value_changed.connect(func(value: float): profile["height"] = value; _refresh_preview())
    _add_field(settings, "Height", height_slider)
    var confirm := Button.new()
    confirm.text = "START MY LIFE"
    confirm.custom_minimum_size.y = 54
    confirm.pressed.connect(_confirm)
    settings.add_child(confirm)
    var viewport_container := SubViewportContainer.new()
    viewport_container.custom_minimum_size = Vector2(380, 540)
    viewport_container.stretch = true
    layout.add_child(viewport_container)
    preview = SubViewport.new()
    preview.size = Vector2i(380, 540)
    preview.transparent_bg = false
    preview.own_world_3d = true
    viewport_container.add_child(preview)
    _build_preview()
    _refresh_preview()

func _add_field(parent: VBoxContainer, title: String, field: Control) -> void:
    var label := Label.new()
    label.text = title
    parent.add_child(label)
    parent.add_child(field)

func _template_changed(index: int) -> void:
    var names := ["Jay", "Esined", "Jahdē"]
    profile["template"] = names[index]
    profile["name"] = names[index]
    # Name field is the third child after the first template label/control.
    var settings := get_node("ScrollContainer") if has_node("ScrollContainer") else null
    if settings != null:
        var layout := settings.get_child(0).get_child(0)
        for node in layout.get_children():
            if node is LineEdit:
                node.text = profile["name"]
    _refresh_preview()

func _set_choice(index: int, key: String) -> void:
    profile[key] = index
    _refresh_preview()

func _build_preview() -> void:
    var root := Node3D.new()
    preview.add_child(root)
    var camera := Camera3D.new()
    camera.position = Vector3(0, 1.3, 4.6)
    camera.look_at(Vector3(0, 1.0, 0))
    camera.current = true
    root.add_child(camera)
    var light := DirectionalLight3D.new()
    light.rotation_degrees = Vector3(-35, -25, 0)
    root.add_child(light)
    var ambient := WorldEnvironment.new()
    var env := Environment.new()
    env.background_mode = Environment.BG_COLOR
    env.background_color = Color("#34405b")
    env.ambient_light_source = Environment.AMBIENT_SOURCE_COLOR
    env.ambient_light_color = Color.WHITE
    ambient.environment = env
    root.add_child(ambient)
    preview_body = _sphere(root, Vector3(0, 0.9, 0), Vector3(0.55, 0.85, 0.3))
    preview_head = _sphere(root, Vector3(0, 1.72, 0), Vector3(0.32, 0.39, 0.32))
    preview_hair = _sphere(root, Vector3(0, 2.01, 0), Vector3(0.34, 0.16, 0.34))
    for x in [-0.12, 0.12]:
        preview_eyes.append(_sphere(root, Vector3(x, 1.76, 0.303), Vector3(0.045, 0.05, 0.018)))

func _sphere(parent: Node3D, pos: Vector3, scale_value: Vector3) -> MeshInstance3D:
    var node := MeshInstance3D.new()
    node.mesh = SphereMesh.new()
    node.position = pos
    node.scale = scale_value
    parent.add_child(node)
    return node

func _color(node: MeshInstance3D, value: Color) -> void:
    var material := StandardMaterial3D.new()
    material.albedo_color = value
    node.material_override = material

func _refresh_preview() -> void:
    if preview_body == null:
        return
    _color(preview_body, Color(OUTFIT_COLORS[int(profile["outfit"])]))
    _color(preview_head, Color(SKIN_COLORS[int(profile["skin"])]))
    preview_head.scale.x = [0.28, 0.32, 0.37][int(profile["face_shape"])]
    _color(preview_hair, Color(HAIR_COLORS[int(profile["hair_color"])]))
    for eye in preview_eyes:
        _color(eye, Color(EYE_COLORS[int(profile["eye_color"])]))
    preview_hair.visible = int(profile["hair_style"]) != 4
    var hair_scale := [0.16, 0.25, 0.4, 0.32, 0.0][int(profile["hair_style"])]
    preview_hair.scale.y = hair_scale
    preview_body.scale.x = [0.43, 0.55, 0.7][int(profile["body_build"])]
    preview_body.scale.y = 0.85 * float(profile["height"])

func _confirm() -> void:
    if str(profile["name"]).strip_edges().is_empty():
        profile["name"] = profile["template"]
    confirmed.emit(profile.duplicate(true))
