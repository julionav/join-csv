# join-csv

Join CSV allows to join multiple CSV files in order, removing duplicated rows.

# Installation

```sh
yarn add join-csv # or npm install join-csv
```

# Usage

### join

Joins an array of csv strings, duplicated rows are removed, remaining the ones that
appeared early

```js
import { join, joinFiles, joinFilesWithOutput } from "join-csv";

const csv1 = `name,price
juice,1000
ice cream,2000
coffee,300`;

const csv2 = `name,price
coffee,300
ice,600
something,20000`;

console.log(join([csv1, csv2]));
`name,price
juice,1000
ice cream,2000
coffee,300
ice,600
something,20000`;
```

### joinFiles

Same as join but takes an array of paths to the csv files

### joinFilesWithOutput

Same as joinFiles but takes a second parameter that specifies a path to save the result of
the join
