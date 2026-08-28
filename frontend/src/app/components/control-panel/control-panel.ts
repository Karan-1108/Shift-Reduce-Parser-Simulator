import { Component, EventEmitter, Output } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-control-panel',
  template: `
    <div class="control-box">
      <label for="expr">Input Arithmetic Expression:</label>
      <div class="input-row">
        <input id="expr" #exprInput type="text" value="a + b * c" (keyup.enter)="submit(exprInput.value)">
        <button (click)="submit(exprInput.value)">Parse Expression</button>
      </div>
    </div>
  `,
  styles: [`
    .control-box { margin-bottom: 20px; }
    label { font-weight: bold; display: block; margin-bottom: 8px; font-size: 15px; }
    .input-row { display: flex; gap: 10px; }
    input { flex: 1; padding: 10px; font-size: 16px; border: 1px solid #ccc; border-radius: 4px; }
    button { padding: 10px 20px; font-size: 16px; background: #007bff; color: white; border: none; border-radius: 4px; cursor: pointer; }
    button:hover { background: #0056b3; }
  `]
})
export class ControlPanelComponent {
  @Output() parse = new EventEmitter<string>();

  submit(val: string) {
    if (val.trim()) this.parse.emit(val.trim());
  }
}