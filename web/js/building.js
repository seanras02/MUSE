
var scene = new THREE.Scene();


var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
camera.position.z = 20;


var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);


var loader = new THREE.GLTFLoader();
loader.load('models/amsterdambuilding.glb', function (gltf) {
    model = gltf.scene;
    scene.add(model);
});


var ambientLight = new THREE.AmbientLight(0xffffff, 0.5);
scene.add(ambientLight);
var directionalLight = new THREE.DirectionalLight(0xffffff, 0.5);
scene.add(directionalLight);

// Interactive controls
var isDragging = false;
var previousMousePosition = {
    x: 0,
    y: 0
};

document.addEventListener('mousedown', function(event) {
    isDragging = true;
});

document.addEventListener('mousemove', function(event) {
    var deltaMove = {
        x: event.clientX - previousMousePosition.x,
        y: event.clientY - previousMousePosition.y
    };

    if (isDragging) {
        var deltaRotationQuaternion = new THREE.Quaternion().setFromEuler(
            new THREE.Euler(
                toRadians(deltaMove.y * 1),
                toRadians(deltaMove.x * 1),
                0,
                'XYZ'
            )
        );

        model.quaternion.multiplyQuaternions(deltaRotationQuaternion, model.quaternion);
    }

    previousMousePosition = {
        x: event.clientX,
        y: event.clientY
    };
});

document.addEventListener('mouseup', function(event) {
    isDragging = false;
});

function toRadians(degrees) {
    return degrees * (Math.PI / 180);
}


function animate() {
    requestAnimationFrame(animate);
    renderer.render(scene, camera);
}
animate();

function resetPage() {
  location.reload();
}