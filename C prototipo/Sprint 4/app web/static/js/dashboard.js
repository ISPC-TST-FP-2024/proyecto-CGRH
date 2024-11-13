document.addEventListener("DOMContentLoaded", function() {
    const tableBody = document.querySelector("#data-table tbody");
    const loader = document.createElement('div');
    loader.textContent = "Cargando datos...";
    loader.classList.add('loader');
    tableBody.appendChild(loader);

    fetch('/api/datos')
        .then(response => {
            if (!response.ok) throw new Error('Error en la respuesta de la API');
            return response.json();
        })
        .then(data => {
            tableBody.innerHTML = data.map(d => `
                <tr>
                    <td>${d.nodo_id}</td>
                    <td>${d.temperatura.toFixed(2)}</td>
                    <td>${d.humedad.toFixed(2)}</td>
                    <td>${d.luz_ambiente}</td>
                    <td>${d.humedad_suelo_cap}</td>
                    <td>${d.humedad_suelo_res}</td>
                    <td>${d.nivel_agua}</td>
                    <td>${d.dispositivo_id}</td>
                </tr>`).join('');
            
            const labels = data.map(d => `Nodo ${d.nodo_id}`);
            const tempData = data.map(d => d.temperatura);
            const humData = data.map(d => d.humedad);
            const luzData = data.map(d => d.luz_ambiente);

            const createChart = (id, label, data, color) => {
                return new Chart(document.getElementById(id), {
                    type: 'line',
                    data: {
                        labels: labels,
                        datasets: [{
                            label: label,
                            data: data,
                            borderColor: color,
                            backgroundColor: `${color}4D`,
                            fill: true
                        }]
                    },
                    options: { responsive: true, maintainAspectRatio: false }
                });
            };

            createChart('tempChart', 'Temperatura (°C)', tempData, '#007bff');
            createChart('humChart', 'Humedad (%)', humData, '#28a745');
            createChart('luzChart', 'Luz Ambiente', luzData, '#ffc107');
        })
        .catch(error => {
            console.error('Error:', error);
            tableBody.innerHTML = '<tr><td colspan="8">Error al cargar datos</td></tr>';
        });
});
