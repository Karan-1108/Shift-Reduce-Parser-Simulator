import { Component, EventEmitter, Output } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-control-panel',
  templateUrl: './control-panel.html',
  styleUrls: ['./control-panel.css']
})
export class ControlPanelComponent {
  @Output() parse = new EventEmitter<string>();

  submit(val: string) {
    if (val.trim()) this.parse.emit(val.trim());
  }
}