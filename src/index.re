[@bs.module]
external parseCSV: string => array(array(string)) = "csv-parse/lib/sync";

[@bs.module]
external stringifyCSV: array(array(string)) => string =
  "csv-stringify/lib/sync";

let readFile = filename => Node_fs.readFileSync(filename, `utf8);

let writeToFile = (filename, data) =>
  Node_fs.writeFileSync(filename, data, `utf8);

let joinRows = Array.map(Js.Array.joinWith(","));

let csvToStringArray = csv => parseCSV(csv)->joinRows;

let uniqueElements = arrays => {
  let seen = Belt.MutableSet.String.make();
  let all = Array.concat(arrays);
  Belt.Array.reduce(all, [||], (acc, current) =>
    if (Belt.MutableSet.String.has(seen, current)) {
      acc;
    } else {
      Belt.MutableSet.String.add(seen, current);
      Array.concat([acc, [|current|]]);
    }
  );
};

let splitRow = row => String.split_on_char(',', row)->Array.of_list;

let join = csvs => {
  let csvArrays = Array.map(csvToStringArray, csvs);
  let uniqueRows = Array.to_list(csvArrays)->uniqueElements;
  let newCsvArray = Array.map(splitRow, uniqueRows);
  stringifyCSV(newCsvArray);
};

let joinFiles = filenames => {
  filenames |> Array.map(readFile) |> join;
};

let joinFilesWithOutput = (filenames, outputName) => {
  joinFiles(filenames) |> writeToFile(outputName);
};