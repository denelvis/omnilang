import { InventoryService } from '../src/services/InventoryService';
import { ItemId, Item } from '../src/types';
import fc from 'fast-check';

describe('InventoryService', () => {
  let service: InventoryService;

  beforeEach(() => {
    service = new InventoryService();
  });

  test('addItem increases quantity', () => {
    const id: ItemId = 'item-1';
    service.items.set(id, { id, qty: 10 });
    const result = service.addItem(id, 5);
    expect(result).toBe(15);
    expect(service.items.get(id)?.qty).toBe(15);
  });

  test('addItem property-based verification', () => {
    fc.assert(
      fc.property(fc.string(), fc.integer({ min: 1 }), (id, qty) => {
        const localService = new InventoryService();
        localService.addItem(id, qty);
        expect(localService.items.get(id)?.qty).toBe(qty);
      })
    );
  });
});
