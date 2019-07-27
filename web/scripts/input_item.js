class InputItem {
    constructor() {
        this.id = -1;
        this.name = '';
        this.type = '';
        this.readOnly = '';
        this.address = '';
        this.words = -1;
        this.formula = '';
    }

    generate() {
        const card = new InputItemBuilder(this.id, this.name, this.address, this.words);
        console.log(this.type);
        if (this.type === dateType.math) {
            card.addMathDataType(this.formula);
        } else if (this.type === dateType.date) {
            card.addDateDataType();
        }
        card.addGetValueInput();
        if (this.readOnly === false) {
            card.addSetValueInput();
        }
        return card.build();
    }
}

class InputItemBuilder {
    constructor(id, name, address, words) {
        this.id = id;
        this.card = `
        <div id="input_${this.id}" class="col-md-4" style="height: 220px;">
                <div class="card border-light bg-light h-100">
                    <div class="card-body">
                        <div class="row">
                            <div class="col-md-8 offset-md-2 text-center">
                                <h5 class="card-title">${name}</h5>
                            </div>
                            <div class="col-md-2 text-right" style="cursor: pointer" onclick="layout.removeInput(${this.id})">
                                <span class="alert alert-danger"><i class="fa fa-times"></i></span>
                            </div>
                        </div>
                        <div class="row">
                            <div class="col-md-12">
                                <p class="card-subtitle text-left">Input for address: <code>${address}</code>, num of words: <code>${words}</code></p>
                            </div>
                        </div>
                        
        `;
    }

    addDateDataType() {
        this.card += `
        <div class="row">
            <div class="col-md-12">
                <p class="card-subtitle text-left">Date data type</p>
            </div>
        </div>`;
        return this;
    }

    addMathDataType(formula) {
        this.card += `
        <div class="row">
            <div class="col-md-12">
                <p class="card-subtitle text-left">Value will be computed by formula: <code>${formula}</code></p>
            </div>
        </div>`;
        return this;
    }

    addGetValueInput() {
        this.card += `
        <div class="row mt-2">
            <div class="col-md-4">
                <button class="btn btn-primary w-100">Get value</button>
            </div>
            <div class="col-md-8">
                <label class="sr-only" for="itemGetValue_${this.id}"></label>
                <input type="text" class="form-control" id="itemGetValue_${this.id}" readonly>
            </div>
        </div>`;
        return this;
    }

    addSetValueInput() {
        this.card += `
        <div class="row mt-2">
            <div class="col-md-8">
                <label class="sr-only" for="inputSetValue_${this.id}">Words</label>
                <input type="text" class="form-control" id="inputSetValue_${this.id}" placeholder="words">
                <div id="inputSetValue_${this.id}" class="invalid-tooltip"></div>
            </div>
            <div class="col-md-4">
                <button class="btn btn-primary w-100">Set value</button>
            </div>
        </div>`;
        return this;
    }

    build() {
        this.card += `</div></div></div></div>`;
        return this.card;
    }
}