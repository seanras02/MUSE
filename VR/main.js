AFRAME.registerComponent('multiple-characters', {
    init: function () {
        const sceneEl = this.el;
        const characterCount = 10;
        const initialZ = -30;
        const maxZ = -50;
        const minX = -20;
        const maxX = 20;

        for (let i = 0; i < characterCount; i++) {
            const z = initialZ - Math.random() * (initialZ - maxZ);
            const x = minX + Math.random() * (maxX - minX);
            const entity = document.createElement('a-entity');
            entity.setAttribute('gltf-model', '#characterModel');
            entity.setAttribute('position', { x: x, y: -0.05, z: z });
            entity.setAttribute('animation-mixer', '');
            entity.setAttribute('animation', `property: position; to: ${x} -0.05 1.5; dur: 32500; easing: linear; loop: true`);
            sceneEl.appendChild(entity);
        }
    }
});