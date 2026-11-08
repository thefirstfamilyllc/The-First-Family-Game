extends CharacterBody3D
class_name FamilyPlayer

@export var speed: float = 4.8
@export var gravity: float = 22.0
var destination: Vector3
var has_destination := false
var character_name := "Jay"
var energy := 100.0
var camera_pivot: Node3D
var model: Node3D

func _ready() -> void:
    destination = global_position
    _create_visuals()
    camera_pivot = Node3D.new()
    camera_pivot.position = Vector3(0, 1.6, 0)
    add_child(camera_pivot)
    var camera := Camera3D.new()
    camera.position = Vector3(0, 5.0, 8.5)
    camera.rotation_degrees.x = -27
    camera.current = true
    camera_pivot.add_child(camera)

func _create_visuals() -> void:
    # Replace this procedural mannequin with a licensed rigged GLB character.
    # Movement and interaction code will remain intact.
    model = Node3D.new()
    add_child(model)
    var capsule := CapsuleMesh.new()
    capsule.radius = 0.33
    capsule.height = 1.6
    var body := MeshInstance3D.new()
    body.mesh = capsule
    var surface := StandardMaterial3D.new()
    surface.albedo_color = Color("#713fa7")
    body.material_override = surface
    body.position.y = 0.9
    model.add_child(body)
    var collider := CollisionShape3D.new()
    var shape := CapsuleShape3D.new()
    shape.radius = 0.34
    shape.height = 1.7
    collider.shape = shape
    collider.position.y = 0.9
    add_child(collider)

func move_to(world_position: Vector3) -> void:
    destination = world_position
    has_destination = true

func _physics_process(delta: float) -> void:
    var movement := Vector3.ZERO
    var manual := Input.get_vector("move_left", "move_right", "move_forward", "move_backward")
    if manual.length() > 0.1:
        has_destination = false
        movement = Vector3(manual.x, 0, manual.y)
    elif has_destination:
        var difference := destination - global_position
        difference.y = 0
        if difference.length() < 0.3:
            has_destination = false
        else:
            movement = difference.normalized()
    velocity.x = movement.x * speed
    velocity.z = movement.z * speed
    if not is_on_floor():
        velocity.y -= gravity * delta
    else:
        velocity.y = -0.1
    if movement.length() > 0.01:
        model.rotation.y = lerp_angle(model.rotation.y, atan2(movement.x, movement.z), delta * 9)
    move_and_slide()
