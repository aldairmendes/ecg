#include "modelo_ecg_export.h"

void score(const double* input, double* output) {
    if (input[4] <= 0.20381072908639908) {
        if (input[32] <= 0.21141739189624786) {
            if (input[32] <= 0.16156228631734848) {
                if (input[3] <= 0.32738177478313446) {
                    if (input[82] <= 0.81551551818847656) {
                        if (input[86] <= 0.89297261834144592) {
                            if (input[117] <= 0.99443459510803223) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                if (input[127] <= 0.07522446289658546) {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        } else {
                            if (input[70] <= 0.23873236775398254) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        }
                    } else {
                        if (input[70] <= 0.07430970109999180) {
                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        } else {
                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    }
                } else {
                    if (input[110] <= 0.41285187378525734) {
                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    } else {
                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    }
                }
            } else {
                if (input[47] <= 0.12498017773032188) {
                    if (input[105] <= 0.06309253349900246) {
                        if (input[5] <= 0.15726910531520844) {
                            if (input[33] <= 0.11259861290454865) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    } else {
                        if (input[123] <= 0.22128834575414658) {
                            if (input[3] <= 0.28682929277420044) {
                                if (input[4] <= 0.01513380161486566) {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            } else {
                                if (input[85] <= 0.28258552402257919) {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        } else {
                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    }
                } else {
                    if (input[25] <= 0.30518813431262970) {
                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    } else {
                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    }
                }
            }
        } else {
            if (input[108] <= 0.02504663728177547) {
                if (input[45] <= 0.37343223392963409) {
                    if (input[28] <= 0.32863909006118774) {
                        if (input[34] <= 0.38174159824848175) {
                            if (input[42] <= 0.08290482684969902) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                if (input[99] <= 0.60867986083030701) {
                                    if (input[129] <= 0.09513420239090919) {
                                        if (input[94] <= 0.96467661857604980) {
                                            if (input[84] <= 0.99790292978286743) {
                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            } else {
                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            }
                                        } else {
                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        }
                                    } else {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        } else {
                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    } else {
                        if (input[95] <= 0.22020082920789719) {
                            if (input[2] <= 0.03203803114593029) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                if (input[3] <= 0.31841549277305603) {
                                    if (input[8] <= 0.33028306066989899) {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                } else {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        } else {
                            if (input[63] <= 0.31027540564537048) {
                                if (input[107] <= 0.05143951624631882) {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            } else {
                                if (input[12] <= 0.24800538271665573) {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    if (input[89] <= 0.00827153492718935) {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (input[76] <= 0.89617371559143066) {
                        if (input[78] <= 0.95776772499084473) {
                            if (input[79] <= 0.96440276503562927) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    } else {
                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    }
                }
            } else {
                if (input[71] <= 0.48438499867916107) {
                    if (input[83] <= 0.31086811423301697) {
                        if (input[162] <= 0.18247328698635101) {
                            if (input[31] <= 0.32342770695686340) {
                                if (input[53] <= 0.13300161808729172) {
                                    if (input[120] <= 0.01866915635764599) {
                                        if (input[5] <= 0.04421189241111279) {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            if (input[19] <= 0.06489755213260651) {
                                                if (input[85] <= 0.02584248548373580) {
                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                } else {
                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                }
                                            } else {
                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            }
                                        }
                                    } else {
                                        if (input[37] <= 0.09437352791428566) {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            if (input[92] <= 0.19593113660812378) {
                                                if (input[103] <= 0.98147565126419067) {
                                                    if (input[91] <= 0.00136054423637688) {
                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                    } else {
                                                        if (input[10] <= 0.00028851701063104) {
                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        } else {
                                                            if (input[6] <= 0.16946004331111908) {
                                                                if (input[1] <= 0.99145260453224182) {
                                                                    if (input[83] <= 0.23097932338714600) {
                                                                        if (input[114] <= 0.00100908172316849) {
                                                                            if (input[96] <= 0.04927159845829010) {
                                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                            } else {
                                                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                            }
                                                                        } else {
                                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                        }
                                                                    } else {
                                                                        if (input[32] <= 0.25519023090600967) {
                                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                        } else {
                                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (input[116] <= 0.10195799358189106) {
                                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                    } else {
                                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                    }
                                                                }
                                                            } else {
                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (input[32] <= 0.26139423251152039) {
                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                    } else {
                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                    }
                                                }
                                            } else {
                                                if (input[47] <= 0.08666938170790672) {
                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                } else {
                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (input[2] <= 0.15140139311552048) {
                                        if (input[107] <= 0.42505413293838501) {
                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        }
                                    } else {
                                        if (input[34] <= 0.28905081748962402) {
                                            if (input[30] <= 0.31598798930644989) {
                                                if (input[114] <= 0.76764392852783203) {
                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                } else {
                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                }
                                            } else {
                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            }
                                        } else {
                                            if (input[133] <= 0.16535391658544540) {
                                                if (input[88] <= 0.22354236990213394) {
                                                    if (input[50] <= 0.13010124489665031) {
                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                    } else {
                                                        if (input[109] <= 0.08483018353581429) {
                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        } else {
                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        }
                                                    }
                                                } else {
                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                }
                                            } else {
                                                if (input[74] <= 0.20258303731679916) {
                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                } else {
                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (input[13] <= 0.05329410918056965) {
                                    if (input[107] <= 0.09567626193165779) {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                } else {
                                    if (input[43] <= 0.34635128080844879) {
                                        if (input[6] <= 0.02925813198089600) {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            if (input[79] <= 0.04621725529432297) {
                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            } else {
                                                if (input[116] <= 0.30819362401962280) {
                                                    if (input[54] <= 0.07113763689994812) {
                                                        if (input[108] <= 0.07229883223772049) {
                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        } else {
                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        }
                                                    } else {
                                                        if (input[82] <= 0.29129098355770111) {
                                                            if (input[96] <= 0.87101590633392334) {
                                                                if (input[65] <= 0.38835190236568451) {
                                                                    if (input[32] <= 0.31732197105884552) {
                                                                        if (input[127] <= 0.04280701652169228) {
                                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                        } else {
                                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                        }
                                                                    } else {
                                                                        if (input[110] <= 0.00061977066798136) {
                                                                            if (input[2] <= 0.02299142722040415) {
                                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                            } else {
                                                                                if (input[19] <= 0.31656923890113831) {
                                                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                } else {
                                                                                    if (input[24] <= 0.51498740911483765) {
                                                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                    } else {
                                                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                    }
                                                                                }
                                                                            }
                                                                        } else {
                                                                            if (input[3] <= 0.39899072051048279) {
                                                                                if (input[107] <= 0.43334372341632843) {
                                                                                    if (input[102] <= 0.96379658579826355) {
                                                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                    } else {
                                                                                        if (input[69] <= 0.11694836616516113) {
                                                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                        } else {
                                                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                        }
                                                                                    }
                                                                                } else {
                                                                                    if (input[107] <= 0.50950750708580017) {
                                                                                        if (input[17] <= 0.20099259912967682) {
                                                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                        } else {
                                                                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                        }
                                                                                    } else {
                                                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                    }
                                                                                }
                                                                            } else {
                                                                                if (input[54] <= 0.16861011832952499) {
                                                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                } else {
                                                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                }
                                                            } else {
                                                                if (input[41] <= 0.31614924967288971) {
                                                                    if (input[39] <= 0.15542788803577423) {
                                                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                    } else {
                                                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                    }
                                                                } else {
                                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                }
                                                            }
                                                        } else {
                                                            if (input[81] <= 0.29058769345283508) {
                                                                if (input[73] <= 0.42810985445976257) {
                                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                } else {
                                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                }
                                                            } else {
                                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (input[40] <= 0.22256468981504440) {
                                                        if (input[0] <= 0.99751088023185730) {
                                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                        } else {
                                                            if (input[114] <= 0.20251045376062393) {
                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            } else {
                                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            }
                                                        }
                                                    } else {
                                                        if (input[102] <= 0.44038350880146027) {
                                                            if (input[124] <= 0.44757740199565887) {
                                                                if (input[3] <= 0.37198637425899506) {
                                                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                } else {
                                                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                                }
                                                            } else {
                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            }
                                                        } else {
                                                            if (input[20] <= 0.31364039331674576) {
                                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            } else {
                                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (input[34] <= 0.44207344949245453) {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            if (input[116] <= 0.04493526369333267) {
                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            } else {
                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (input[54] <= 0.17736884206533432) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                if (input[102] <= 0.12411837652325630) {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        }
                    } else {
                        if (input[23] <= 0.43172311782836914) {
                            if (input[40] <= 0.53709611296653748) {
                                if (input[88] <= 0.07946415245532990) {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    if (input[4] <= 0.11277804151177406) {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        if (input[4] <= 0.13854278624057770) {
                                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        }
                                    }
                                }
                            } else {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            if (input[5] <= 0.08211755380034447) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                if (input[94] <= 0.26886424422264099) {
                                    if (input[51] <= 0.34106084704399109) {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        }
                    }
                } else {
                    if (input[89] <= 0.85786074399948120) {
                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    } else {
                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    }
                }
            }
        }
    } else {
        if (input[4] <= 0.26186379790306091) {
            if (input[86] <= 0.05428249016404152) {
                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
            } else {
                if (input[5] <= 0.14221280068159103) {
                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                } else {
                    if (input[60] <= 0.25399120151996613) {
                        if (input[58] <= 0.18569575995206833) {
                            if (input[14] <= 0.09955752268433571) {
                                if (input[121] <= 0.17616576328873634) {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            } else {
                                if (input[96] <= 0.62891788780689240) {
                                    if (input[133] <= 0.59035772085189819) {
                                        if (input[104] <= 0.83283114433288574) {
                                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                        } else {
                                            if (input[31] <= 0.35225324332714081) {
                                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            } else {
                                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                            }
                                        }
                                    } else {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            }
                        } else {
                            if (input[3] <= 0.28342533111572266) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        }
                    } else {
                        if (input[40] <= 0.52942311763763428) {
                            if (input[82] <= 0.25351800769567490) {
                                if (input[23] <= 0.33356752991676331) {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    if (input[89] <= 0.46914884448051453) {
                                        output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    } else {
                                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                    }
                                }
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            if (input[107] <= 0.49211469292640686) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        }
                    }
                }
            }
        } else {
            if (input[131] <= 0.91106867790222168) {
                if (input[2] <= 0.13666829466819763) {
                    if (input[12] <= 0.29952536523342133) {
                        if (input[56] <= 0.15339059382677078) {
                            output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        } else {
                            output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                        }
                    } else {
                        output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                    }
                } else {
                    if (input[9] <= 0.11414687708020210) {
                        if (input[99] <= 0.37613703310489655) {
                            if (input[128] <= 0.29479286074638367) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            if (input[84] <= 0.23579975962638855) {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        }
                    } else {
                        if (input[45] <= 0.08961306139826775) {
                            if (input[45] <= 0.08569916337728500) {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            } else {
                                output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        } else {
                            if (input[1] <= 0.64223152399063110) {
                                if (input[1] <= 0.64171546697616577) {
                                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                } else {
                                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                                }
                            } else {
                                output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                            }
                        }
                    }
                }
            } else {
                if (input[117] <= 0.14066616445779800) {
                    output[0] = 1.0; output[1] = 0.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                } else {
                    output[0] = 0.0; output[1] = 1.0; output[2] = 0.0; output[3] = 0.0; output[4] = 0.0;
                }
            }
        }
    }
}
