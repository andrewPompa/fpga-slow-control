class ChartItem {
    constructor(id, name, interval, dataSets) {
        this.id = id;
        this.name = name;
        this.interval = interval;
        this.dataSets = dataSets;
        this.chart = null;
    }

    buildCanvas() {
        return `
            <div class="col-xl-6">
                <canvas id="chart_${this.id}" ></canvas>
            </div>
        `;
    }

    valueForConfiguration() {
        return {
            id: this.id,
            name: this.name,
            interval: this.interval,
            series: this.dataSets,
        };
    }

    buildChart() {
        const ctx = $(`#chart_${this.id}`)[0].getContext('2d');
        const datasets = this.dataSets.map(dataset => {
            const colour = Math.floor(Math.random() * 255) + ', ' + Math.floor(Math.random() * 255) + ', ' + Math.floor(Math.random() * 255);
            return {
                label: dataset.name,
                backgroundColor: `rgba(${colour}, 0.5)`,
                borderColor: `rgb(${colour})`,
                data: [],
                address: dataset.address,
                dataType: dataset.dataType,
                formula: dataset.formula
            };
        });
        this.chart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: [],
                datasets: datasets
            },
            options: {
                title: {display: true, text: this.name}
            }
        });
        this.intervalId = setInterval(() => this.tickFunction(), this.interval);
    }

    tickFunction() {
        this.chart.data.labels.push(currentTimeInMillis());
        this.chart.data.datasets.forEach(dataset => {
            if (dataset.dataType === dateType.hex) {
                wordService.getInt(dataset.address, (value) => this.addData(value, dataset));
            } else if (dataset.dataType === dateType.math) {
                wordService.getMath(dataset.address, dataset.formula, (value) => this.addData(value, dataset));
            }

        });

    }

    addData(value, dataset) {
        dataset.data.push(value);
        this.chart.update();
    }

    removeInterval() {
        clearInterval(this.intervalId);
    }

}