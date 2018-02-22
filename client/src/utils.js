// @flow
/**
 * creates a Map that maps between values and their indexes
 */
export function arrayToMap<T>(arr: T[]): Map<T, number> {
  const map = new Map();

  for (let i = 0; i < arr.length; i++) {
    map.set(arr[i], i);
  }
  return map;
}

};
