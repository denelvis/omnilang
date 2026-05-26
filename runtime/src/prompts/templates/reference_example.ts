import { ItemId, Item } from '../types';
export { ItemId, Item };

export class InventoryService {
  public items = new Map<ItemId, Item>();

  public addItem(id: ItemId, qty: number): number {
    if (qty <= 0) {
      throw new Error('Quantity must be positive');
    }
    let item = this.items.get(id);
    if (!item) {
      item = { id, qty: 0 };
      this.items.set(id, item);
    }
    item.qty += qty;
    return item.qty;
  }
}
