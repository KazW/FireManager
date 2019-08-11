export function validate(host: string, network: string, password: string): {
  error: boolean,
  errors: {
    "Device Name": string[],
    "Network Name": string[],
    "Network Password": string[]
  }
} {
  let hostErrors = validateHost(host);
  let networkErrors = validateNetwork(network);
  let passwordErrors = validatePassword(password);

  return {
    error:
      notEmpty(hostErrors)
      || notEmpty(networkErrors)
      || notEmpty(passwordErrors),
    errors: {
      "Device Name": hostErrors,
      "Network Name": networkErrors,
      "Network Password": passwordErrors
    }
  };
};

function notEmpty(errors: string[]): boolean {
  return errors.length > 0;
}

function validateHost(host: string): string[] {
  let errors = [];

  if (/^\d/.test(host)) errors.push("Cannot start with a number.");
  if (host.length < 3) errors.push("Must be 3 characters or longer.");
  if (host.length > 23) errors.push("Must be 23 characters or less.");
  if (/[^a-z0-9_-]/.test(host)) errors.push("Can only contain characters: a-z (lowercase), 0-9, dashes and underscores.");

  return errors;
};

function validateNetwork(network: string): string[] {
  let errors = [];

  if (network.length > 32) errors.push("Must be 32 characters or less.");
  if (/^[!;#]/.test(network)) errors.push("Cannot start with: ! or ; or #.");
  if (/^[\+\]/"\t]/.test(network)) errors.push("Cannot contain: + or ] or / or \" or tabs.");
  if (/[ ]$/.test(network)) errors.push("Cannot end with spaces.");
  if (/[^\x00-\x7F]/.test(network)) errors.push("Can only contain ascii characters.");

  return errors;
};

function validatePassword(password: string): string[] {
  let errors = [];

  if (password.length < 8) errors.push("Must be 8 characters or longer.");
  if (password.length > 64) errors.push("Must be 64 characters or less.");
  if (/[^\x00-\x7F]/.test(password)) errors.push("Can only contain ascii characters.");

  return errors;
};
