#!/usr/bin/env php
<?php
/******************************************************************
*  Converts Keil style header scripts to SDCC
*
******************************************************************/

if(isset($argc) && $argc >= 3) {
    $inHnd = @fopen($argv[1], "r");
    $outHnd = @fopen($argv[2], "x");
    if($inHnd && $outHnd) {
        $sfrs = [];
        $sfr_pattern = '/(\bsfr)(\s+)(\w{1,8})(\s+)=(\s+)(\w{4})(.+[\r\n])/i';
        $sbit_pattern = '/(\bsbit)(\s+)(\w{1,8})(\s+)=(\s+)(\w{1,8})\^(\d)(.+[\r\n])/i';
        $patterns = [];
        $patterns[0] = $sfr_pattern;
        $patterns[1] = $sbit_pattern;
        $replacements = [];
        $replacements[0] = '__sfr __at ($6) $3$7';
        $replacements[1] = '__sbit __at $6^$7 $3$8';
        while (($line = fgets($inHnd, 1024)) !== false) {
            $new_line = preg_replace($patterns, $replacements, $line);
            if(preg_match($sfr_pattern, $line)) {
                $sfrs[preg_replace($sfr_pattern, '$3', $line)] = preg_replace($sfr_pattern, '$6', $line);
            }
            if(preg_match($sbit_pattern, $line)) {
                $idx = preg_replace($sbit_pattern, '$6', $line);
                $new_line = str_replace("$idx^", "$sfrs[$idx]^", $new_line);
            }
            fwrite($outHnd, $new_line);
        }

        fclose($inHnd);
        fclose($outHnd);
    }
    else {
        if(!$inHnd) {
            echo "Fail to open $argv[1]\n";
        }
        if(!$outHnd) {
            echo "Fail to create $argv[2], or file already exists.\n";
        }
    }

}
else {
    echo "Usage: $argv[0] infile.h outfile.h\n";
}

?>

