// proyecto.js

document.addEventListener("DOMContentLoaded", function () {
    // Animación de fade-in al cargar la página
    const elements = document.querySelectorAll('.fade-in');
    elements.forEach(element => {
        setTimeout(() => {
            element.style.transition = 'opacity 1.5s ease-in-out';
            element.style.opacity = 1;
        }, 300);
    });

    // Efecto hover en las imágenes
    const images = document.querySelectorAll('.img-zoom');
    images.forEach(img => {
        img.addEventListener('mouseover', () => {
            img.style.transform = 'scale(1.1)';
        });
        img.addEventListener('mouseout', () => {
            img.style.transform = 'scale(1)';
        });
    });

    // Configuración y muestra de gráficos con Chart.js
    const ctxTemp = document.getElementById('tempChart').getContext('2d');
    new Chart(ctxTemp, {
        type: 'line',
        data: {
            labels: ['Enero', 'Febrero', 'Marzo'],
            datasets: [{
                label: 'Temperatura',
                data: [20, 25, 23],
                borderColor: '#e74c3c',
                borderWidth: 2,
                fill: false,
                tension: 0.1
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
        }
    });
});
